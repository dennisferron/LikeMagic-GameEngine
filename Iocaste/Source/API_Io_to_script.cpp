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
#include "Iocaste/LikeMagicAdapters/ToIoObjectExpr.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"

using namespace LM;

namespace Iocaste { namespace LMAdapters {

// Note:  This is not Io strings-as-sequences, but actually stuff like vector which is implemented as a sequence.
template <typename T>
IoObject* to_seq(std::vector<T> const* vect, IoState* self)
{
    TypeIndex to_type = TypId<T>::get();

    // Yuck!  C-style memory alloc!  NAasty...  At least Io frees it for us (I *think*...)
    T* c_buf = reinterpret_cast<T*>(io_calloc(vect->size(), sizeof(T)));

    // TODO:  change CTYPE depending on T.
    UArray* uarray;

    if (to_type == TypId<int>::get())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_int32_t, CENCODING_NUMBER, vect->size(), 0);
    else if (to_type == TypId<unsigned int>::get())
        uarray = UArray_newWithData_type_encoding_size_copy_(c_buf, CTYPE_uint32_t, CENCODING_NUMBER, vect->size(), 0);
    else
        throw std::logic_error(std::string("No code implemented yet in LikeMagic for converting to IoSeq from ") + to_type.description());

    // In this case all iterators are pointers, so the STL algorithm here actually uses memcpy for efficiency.
    copy(vect->begin(), vect->end(), c_buf);

    // If you created the Sequence first, it would have just made one uarray and then dropped it when
    // you changed things.  So it's better to create the UArray first and then make it into a sequence.
    return IoSeq_newWithUArray_copy_(self, uarray, 0);
}

template <typename T, typename F>
struct ToIoConv : public AbstractTypeConverter
{
    std::string to_type_name;
    F io_func;

    ToIoConv(std::string to_type_name_, F io_func_)
        : to_type_name(to_type_name_), io_func(io_func_) {}

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return ToIoObjectExpr<T, F>::create(expr, io_func);
    }

    virtual std::string description() const { return "To Io " + to_type_name + " Conv"; }

    virtual float cost() const { return 5.0f; }
};

template <typename T, typename F>
void add_to_io_converter(std::string to_type_name, F io_func)
{
    TypeIndex from_type = TypId<T const*>::get();
    TypeIndex to_type = ToIoTypeInfo::create_index();
    auto conv = new ToIoConv<T, F>(to_type_name, io_func);
    type_system->add_converter_simple(from_type, to_type, conv);
    bool has_type_sys_conv = type_system->has_conv(from_type, to_type);
    cout << "add_to_io_converter" << " has_type_sys_conv " << has_type_sys_conv << " from " << from_type.description() << " " << from_type.get_id() << " to " << to_type.description() << " " << to_type.get_id() << " conv " << conv->description() << endl;
}

#define DECL_CONV(name, type, code) \
    add_to_io_converter<type>(#name, [](IoObject *self, IoObject *locals, IoMessage *m, type value) { return code; });

template <typename T>
struct ToNumberFromT : public AbstractTypeConverter
{
    static IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m, T value)
    {
        IoObject* io_obj = IONUMBER(value);
        cout <<
            "To Io Number from " + TypId<T>::get().description() + " Conv"
            << " from value = " << value << " and to io_obj = " << IoNumber_asDouble(io_obj) << endl;
        return io_obj;
    }

    template <typename F>
    static ExprPtr wrap_expr(ExprPtr expr, F io_func)
    {
        return ToIoObjectExpr<T, F>::create(expr, io_func);
    }

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return wrap_expr(expr,
            [](IoObject *self, IoObject *locals, IoMessage *m, T value)
                { return IONUMBER(value); });
    }

    virtual std::string description() const { return "To Io Number from " + TypId<T>::get().description() + " Conv"; }

    static void add_conv()
    {
        type_system->add_converter_simple(TypId<T*>::get(), ToIoTypeInfo::create_index(), new ToNumberFromT<T>());
    }

    virtual float cost() const { return 5.0f; }
};

struct ToIoNilExpr : public AbstractToIoObjectExpr
{
    ExprPtr expr;

    ToIoNilExpr(ExprPtr expr_) :
        AbstractToIoObjectExpr(nullptr, ToIoTypeInfo::create_index()), expr(expr_) {}

    virtual IoObject* eval_in_context(IoObject *self, IoObject *locals, IoMessage *m)
    {
        return IONIL(self);
    }

    virtual std::string description() const
    {
        return "ToIoNilExpr";
    }

    virtual void mark() const { expr->mark(); }

    virtual float cost() const { return 5.0f; }
};

struct ToIoNil : public AbstractTypeConverter
{
    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        auto* result = new ToIoNilExpr(expr);
        return create_expr(result, result->get_type());
    }

    virtual std::string description() const { return "To Io nil Conv"; }

    virtual float cost() const { return 5.0f; }
};

void add_convs_to_script(IoVM* iovm)
{
    DECL_CONV(Number, double, IONUMBER(value))
    DECL_CONV(Bool, bool, value? IOTRUE(self) : IOFALSE(self))
    DECL_CONV(String, std::string, IOSEQ(reinterpret_cast<const unsigned char*>(value.c_str()), value.length()))

    DECL_CONV(Vector_of_Int, std::vector<int> const*, to_seq<int>(value, IOSTATE))
    DECL_CONV(Vector_of_UInt, std::vector<unsigned int> const*, to_seq<unsigned int>(value, IOSTATE))

    type_system->add_converter_simple(TypId<void*>::get(), ToIoTypeInfo::create_index(), new ToIoNil);

    ToNumberFromT<double>::add_conv();
    ToNumberFromT<float>::add_conv();
}

}}
