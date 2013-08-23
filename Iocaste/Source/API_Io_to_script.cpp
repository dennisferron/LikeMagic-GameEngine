// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Exprs/NullExpr.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
#include "Iocaste/LikeMagicAdapters/ToIoObjectExpr.hpp"
#include "Iocaste/LikeMagicAdapters/IoObjectExpr.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

using namespace LM;
using namespace LM;
using namespace LM;

namespace Iocaste { namespace LMAdapters {

// Note:  This is not Io strings-as-sequences, but actually stuff like vector which is implemented as a sequence.
template <typename T>
IoObject* to_seq(std::vector<T> const& vect, IoState* self)
{
    TypeIndex to_type = TypId<T>::get();

    // Yuck!  C-style memory alloc!  NAasty...  At least Io frees it for us (I *think*...)
    T* c_buf = reinterpret_cast<T*>(io_calloc(vect.size(), sizeof(T)));

    // TODO:  change CTYPE depending on T.
    UArray* uarray;

    if (to_type == TypId<int>::get())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_int32_t, CENCODING_NUMBER, vect.size(), 0);
    else if (to_type == TypId<unsigned int>::get())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_uint32_t, CENCODING_NUMBER, vect.size(), 0);
    else
        throw std::logic_error(std::string("No code implemented yet in LikeMagic for converting to IoSeq from ") + to_type.description());

    // In this case all iterators are pointers, so the STL algorithm here actually uses memcpy for efficiency.
    copy(vect.begin(), vect.end(), c_buf);

    // If you created the Sequence first, it would have just made one uarray and then dropped it when
    // you changed things.  So it's better to create the UArray first and then make it into a sequence.
    return IoSeq_newWithUArray_copy_(self, uarray, 0);
}

#define DECL_CONV(name, type, code) \
struct To##name : public AbstractTypeConverter \
{ \
    static IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m, type value) \
    { \
        return code; \
    } \
    \
    virtual ExprPtr wrap_expr(ExprPtr expr) const \
    { \
        return ToIoObjectExpr<type, To##name>::create(expr); \
    } \
\
    virtual std::string description() const { return "To " #name " Conv"; } \
}; \

#define ADD_CONV(name, type) \
type_system->add_converter_simple(TypId<type>::get(), ToIoTypeInfo::create_index(), new To##name);

DECL_CONV(Number, double, IONUMBER(value))
DECL_CONV(Bool, bool, value? IOTRUE(self) : IOFALSE(self))
DECL_CONV(String, std::string, IOSEQ(reinterpret_cast<const unsigned char*>(value.c_str()), value.length()))

DECL_CONV(Vector_of_Int, std::vector<int> const&, to_seq<int>(value, IOSTATE))
DECL_CONV(Vector_of_UInt, std::vector<unsigned int> const&, to_seq<unsigned int>(value, IOSTATE))

template <typename T>
struct ToNumberFromT : public AbstractTypeConverter
{
    static IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m, T value)
    {
        IoObject* io_obj = IONUMBER(value);
        //cout <<
        //    "To Number from " + TypId<T>::get().description() + " Conv"
        //    << " from value = " << value << " and to io_obj = " << IoNumber_asDouble(io_obj) << endl;
        return io_obj;
    }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return ToIoObjectExpr<T, ToNumberFromT>::create(expr);
    }

    virtual std::string description() const { return "To Number from " + TypId<T>::get().description() + " Conv"; }

    static void add_conv()
    {
        type_system->add_converter_simple(TypId<T>::get(), ToIoTypeInfo::create_index(), new ToNumberFromT<T>());
    }
};

struct ToIoNilExpr : public AbstractToIoObjectExpr
{
    ExprPtr expr;

    ToIoNilExpr(ExprPtr expr_) : expr(expr_) {}

    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m)
    {
        return IONIL(self);
    }

    virtual LM::TypeIndex get_type() const
    {
        return ToIoTypeInfo::create_index();
    }

    virtual std::string description() const
    {
        return "ToIoNilExpr";
    }

    virtual void mark() const { expr->mark(); }
};

struct ToIoNil : public AbstractTypeConverter
{
    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return new ToIoNilExpr(expr);
    }

    virtual std::string description() const { return "To nil Conv"; } \
};

void add_convs_to_script(IoVM* iovm)
{
    //ADD_CONV(Number, double)
    //ADD_CONV(Number, float)
    ADD_CONV(Bool, bool)
    ADD_CONV(String, std::string)

    ADD_CONV(Vector_of_Int, std::vector<int> const&)
    ADD_CONV(Vector_of_UInt, std::vector<unsigned int> const&)

    type_system->add_converter_simple(TypId<void>::get(), ToIoTypeInfo::create_index(), new ToIoNil);

    ToNumberFromT<double>::add_conv();
    ToNumberFromT<float>::add_conv();
}

}}
