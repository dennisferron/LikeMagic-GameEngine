// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include "boost/lexical_cast.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

using namespace LM;

extern char const* likemagic_proto_id;
extern char const* likemagic_proto_data;

namespace Iocaste { namespace LMAdapters {

std::string get_type_name(IoObject* io_obj)
{
    // IOSTATE macro needs an IoObject* called "self" to get the tag from.
    IoObject* self = io_obj;

    // Special cases (for when tag->name is incorrect).
    if (ISNIL(io_obj))  // ISBOOL captures nil too, so check for nil first
        return "Nil";
    else if (ISBOOL(io_obj))
        return "Bool";
    else  // For many cases the tag->name will work.
        return IoObject_tag(io_obj)->name;
}


IoMethodTable* make_io_method_table(std::vector<std::string> const& method_names)
{
    IoMethodTable* table;

    typedef IoMethodFunc* MethodPtr;

    int count = method_names.size();

    table = new IoMethodTable[count+1];

    int i = 0;
    for (auto it = method_names.begin(); it != method_names.end(); it++, i++)
    {
        // Io will make a copy of the string's c_str() bytes for method name,
        // and the method names vector object lives inside TypeMirror,
        // so that we can be sure it survives long enough for Io to make the copy.
        IoMethodTable entry = { it->c_str(), &API_io_perform };  // All point to same userfunc
        table[i] = entry;
    }

    IoMethodTable term = { NULL, NULL };
    table[count] = term;

    return table;
}


IoObject* get_io_arg_at(IoObject *self, IoObject *locals, IoMessage *m, int pos)
{
    if (pos >= IoMessage_argCount(m))
        throw std::invalid_argument("Not enough arguments passed to function");

    IoObject* arg = IoMessage_locals_valueArgAt_(m, locals, pos);

    if (!arg)
        throw std::invalid_argument("IoMessage_locals_valueArgAt_ at pos is null!");

    return arg;
}

bool is_Exprs_obj(IoObject* io_obj)
{
    void* data_ptr = IoObject_dataPointer(io_obj);

    return
        data_ptr != nullptr
    &&
        data_ptr != (void const*)likemagic_proto_data
    &&
        std::string(IoObject_tag(io_obj)->name) == std::string("LikeMagic");
}


// Gets the IoState object from an IoObject
IoState* get_io_state(IoObject* self)
{
    return reinterpret_cast<IoState*>(IoObject_tag(self)->state);
}

IoMessage* new_message(IoObject* self, std::string name)
{
    if (!self)
        throw std::logic_error("Cannot create message; self is null!");

    if (!self->object)
        throw std::logic_error("Cannot create message; self has no object!");

    return IoMessage_newWithName_(get_io_state(self), IOSYMBOL(name.c_str()));
}

// Gets the script object argument at a certain position.
ExprPtr get_expr_arg_at(IoObject *self, IoObject *locals, IoMessage *m, int pos, TypeIndex target_type)
{
    //std::cout << "Arg " << pos << " = " << IoObject_tag(self)->name << std::endl;
    return from_script(self, get_io_arg_at(self, locals, m, pos), target_type);
}


}}

IoObject* API_io_rawClone(IoObject* proto)
{
    if (!proto)
        throw std::logic_error("API_io_rawClone called with proto=NULL");

    IoObject* clone = reinterpret_cast<IoObject*>(IoObject_rawClonePrimitive(
            reinterpret_cast<IoObject*>(proto)));

    // Intentionally NOT cloning the pointer to the C++ Expr, if there is one.
    IoObject_setDataPointer_(clone, nullptr);

    return clone;
}

void API_io_free_expr(IoObject* self)
{
    IoObject* io_obj = reinterpret_cast<IoObject*>(self);

    if (ISNUMBER(io_obj))
        throw std::logic_error("free Exprs proxy passed an IoNumber instead!");
    else if (ISSEQ(io_obj))
        throw std::logic_error("free Exprs proxy passed an IoSeq instead!");
    else if (IoObject_dataPointer(self))
    {
        if (is_Exprs_obj(io_obj))
        {
            std::cout << "free Exprs proxy passed Exprs object with tag " << IoObject_tag(io_obj)->name << std::endl;
        }
        else
        {
            std::cout << "free Exprs proxy passed a NON-Exprs object with tag " << IoObject_tag(io_obj)->name << std::endl;
            throw std::logic_error("free Exprs proxy passed a NON-Exprs object");
        }

        void* voidDataPtr = IoObject_dataPointer(self);
        Expr* exprDataPtr = reinterpret_cast<Expr*>(voidDataPtr);

        // For debugging, intentionally not releasing the pointer.
        // TODO:  Put this back when done debugging.
        //intrusive_ptr_release(exprDataPtr);
        //IoObject_setDataPointer_(self, 0);
    }
}

void API_io_mark(IoObject* self)
{
    if (self && IoObject_dataPointer(self))
    {
        IoObject_shouldMark(self);
        auto expr = reinterpret_cast<Expr*>(IoObject_dataPointer(self));
        expr->mark();
    }
}

IoObject* API_io_perform(IoObject *self, IoObject *locals, IoMessage *m)
{
    return IoVM::perform(self, locals, m);
}

IoObject* API_io_forward(IoObject *self, IoObject *locals, IoMessage *m)
{
    return IoVM::forward(self, locals, m);
}

