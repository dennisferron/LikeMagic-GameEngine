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
#include "Iocaste/LikeMagicAdapters/FromIoTypeInfo.hpp"

#include "Iocaste/LikeMagicAdapters/IoListSTL.hpp"
#include "Iocaste/LikeMagicAdapters/IoVectorSTL.hpp"

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/Exprs/ExprTrackingInfo.hpp"

#include <vector>
#include <algorithm>

using namespace LM;

namespace Iocaste { namespace LMAdapters {

template <typename T>
std::vector<T> from_vector(IoObject* io_obj)
{
    IoVectorSTL<T> io_vector(io_obj);

    std::vector<T> cpp_vector(io_vector.size());

    copy(io_vector.begin(), io_vector.end(), cpp_vector.begin());

    return cpp_vector;
}

template <typename T>
std::vector<T> from_list(IoObject* io_obj)
{
    IoListSTL<T> io_list(io_obj);

    std::vector<T> cpp_vector(io_list.size());

    copy(io_list.begin(), io_list.end(), cpp_vector.begin());

    return cpp_vector;
}


//struct FromNumber : public AbstractTypeConverter
//{
//    virtual ExprPtr wrap_expr(ExprPtr expr) const
//    {
//        boost::intrusive_ptr<IoObjectExpr> io_expr = static_cast<IoObjectExpr*>(expr.get());
//        return Term<double, true>::create(IoNumber_asDouble(io_expr->eval()));
//    }
//
//    virtual std::string description() const { return "From Number Conv"; }
//};

template <typename T, typename F>
struct FromIoConv : public AbstractTypeConverter
{
    std::string script_type;
    F io_func;

    FromIoConv(std::string script_type_, F io_func_)
        : script_type(script_type_), io_func(io_func_) {}

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        IoObject* io_obj = reinterpret_cast<IoObject*>(expr->get_value_ptr().as_nonconst);
        return Term<T>::create(io_func(io_obj));
    }

    virtual std::string description() const { return "From " + script_type + " Conv"; }
    virtual float cost() const { return 5.0f; }
};

template <typename T, typename F>
void add_from_io_converter(std::string script_type, F io_func)
{
    auto conv = new FromIoConv<T, F>(script_type, io_func);
    TypeIndex from_type = FromIoTypeInfo::create_index(script_type);
    type_system->add_converter_simple(from_type, TypId<T>::liberal(), conv);

    if (!type_system->has_conv(from_type, TypId<IoObject*>::restricted()))
    {
        type_system->add_converter_simple(from_type, TypId<IoObject*>::restricted(), new NoChangeConv("Io Type to IoObject*"));
    }
}

#define MKCONV(scriptType, cppType, ioFunc) \
    add_from_io_converter<cppType>(#scriptType, [](IoObject* io_obj) { return ioFunc(io_obj); });

void add_convs_from_script(IoVM* iovm)
{
    // Nil requires special handling because it produces not a term but a NullExpr.
    struct FromNil : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            return create_expr(nullptr, create_bottom_ptr_type_index());
        }

        virtual std::string description() const { return "From Nil Conv"; }

        virtual float cost() const { return 5.0f; }
    };
    TypeIndex from_type(FromIoTypeInfo::create_index("Nil"));
    TypeIndex to_type = create_bottom_ptr_type_index();
    auto conv = new FromNil;
    type_system->add_converter_simple(from_type, to_type, conv);

    // Interpret nil as false in bool contexts.
    struct FromNilToFalse : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            return Term<bool>::create(false);
        }

        virtual std::string description() const { return "From Nil to 'false' Conv"; }

        virtual float cost() const { return 5.0f; }
    };
    type_system->add_converter_simple(FromIoTypeInfo::create_index("Nil"), TypId<bool>::restricted(), new FromNilToFalse);

    // Allow nil to convert to void (for IoBlock eval<void>)
    struct FromNilToVoid : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            return nullptr;
        }

        virtual std::string description() const { return "From Nil to void Conv"; }

        virtual float cost() const { return 5.0f; }
    };
    type_system->add_converter_simple(FromIoTypeInfo::create_index("Nil"), TypId<void>::restricted(), new FromNilToVoid);

    struct FromIoBlock : public AbstractTypeConverter
    {
        IoVM* iovm;
        FromIoBlock(IoVM* iovm_) : iovm(iovm_) {}

        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            IoObject* io_obj = reinterpret_cast<IoObject*>(expr->get_value_ptr().as_nonconst);
            if (io_obj->object == nullptr)
                throw std::runtime_error("Source Io object is missing object pointer.");
            return Term<IoBlock>::create(IoBlock(iovm, io_obj, io_obj));
        }

        virtual std::string description() const { return "From Block Conv"; }

        virtual float cost() const { return 5.0f; }
    };

    TypeIndex from_script_block_type = FromIoTypeInfo::create_index("Block");
    TypeIndex to_block_wrapper_type = TypId<IoBlock>::liberal();
    p_conv_t block_converter = new FromIoBlock(iovm);

    type_system->add_converter_simple(
          from_script_block_type,
          to_block_wrapper_type,
          block_converter);

    MKCONV(Number, double, IoNumber_asDouble)
    MKCONV(Number, int, IoNumber_asInt)
    MKCONV(Number, unsigned int, IoNumber_asInt)
    MKCONV(Number, short, (short)IoNumber_asInt)
    MKCONV(Number, unsigned char, (unsigned char)IoNumber_asInt)
    MKCONV(Number, float, IoNumber_asFloat)
    MKCONV(Sequence, std::string, IoSeq_asCString)
    MKCONV(Sequence, char const*, IoSeq_asCString)
    //MKCONV(Bool, bool, ISTRUE)

    struct FromBool : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            IoObject* io_obj = reinterpret_cast<IoObject*>(expr->get_value_ptr().as_nonconst);
            bool value = ISTRUE(io_obj);
            return Term<bool>::create(value);
        }

        virtual std::string description() const { return "From Bool Conv"; }

        virtual float cost() const { return 5.0f; }
    };

    type_system->add_converter_simple(FromIoTypeInfo::create_index("Bool"), TypId<bool>::liberal(), new FromBool);

    struct FromSequenceToWCharConstPtrConv : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            IoObject* io_obj = reinterpret_cast<IoObject*>(expr->get_value_ptr().as_nonconst);
            char const* src = IoSeq_asCString(io_obj);

            ExprPtr result = Term<std::wstring>::create(std::wstring());

            std::wstring* dst =
                reinterpret_cast<std::wstring*>(
                    expr->get_value_ptr().as_nonconst);

            while (*src++)
                *dst += (wchar_t)*src;

            return create_reference(dst->c_str(), TypId<wchar_t const*>::restricted(), result);
        }

        virtual std::string description() const { return "FromSequenceToWCharConstPtrConv"; }

        virtual float cost() const { return 500.0f; }
    };

    type_system->add_converter_simple(FromIoTypeInfo::create_index("Sequence"),
                                      TypId<wchar_t const*>::restricted(),
                                      new FromSequenceToWCharConstPtrConv);

    //MKCONV(Vector, std::vector<long double>, from_vector<long double>)
    MKCONV(Vector, std::vector<double>, from_vector<double>)
    //MKCONV(Vector, std::vector<float>, from_vector<float>)
    //MKCONV(Vector, std::vector<long long>, from_vector<long long>)
    MKCONV(Vector, std::vector<long>, from_vector<long>)
    MKCONV(Vector, std::vector<short>, from_vector<short>)
    //MKCONV(Vector, std::vector<signed char>, from_vector<signed char>)
    //MKCONV(Vector, std::vector<unsigned long long>, from_vector<unsigned long long>)
    MKCONV(Vector, std::vector<unsigned long>, from_vector<unsigned long>)
    MKCONV(Vector, std::vector<unsigned short>, from_vector<unsigned short>)
    //MKCONV(Vector, std::vector<unsigned char>, from_vector<unsigned char>)


    // List elements have to be converted one-by-one.  There's a class, IoListSTL, that does this
    // but only double is implemented.  This strategy needs to be rethought so we can apply
    // a try_conv to all the list elements, but IoList isn't really being used at the moment anyway.

    //MKCONV(List, std::vector<long double>, from_list<long double>)
    MKCONV(List, std::vector<double>, from_list<double>)
    //MKCONV(List, std::vector<float>, from_list<float>)
    //MKCONV(List, std::vector<long long>, from_list<long long>)
    //MKCONV(List, std::vector<long>, from_list<long>)
    //MKCONV(List, std::vector<short>, from_list<short>)
    //MKCONV(List, std::vector<signed char>, from_list<signed char>)
    //MKCONV(List, std::vector<unsigned long long>, from_list<unsigned long long>)
    //MKCONV(List, std::vector<unsigned long>, from_list<unsigned long>)
    //MKCONV(List, std::vector<unsigned short>, from_list<unsigned short>)
    //MKCONV(List, std::vector<unsigned char>, from_list<unsigned char>)
}

ExprPtr from_script(IoObject* self, IoObject* io_obj, TypeIndex to_type)
{
    TypeIndex wants_io_obj = TypId<IoObject*>::restricted();

    if (is_Exprs_obj(io_obj) && !(to_type == wants_io_obj))
    {
        Expr* expr =
                reinterpret_cast<Expr*>
                    (IoObject_dataPointer(io_obj));
        assert_expr(expr);
        return expr;
    }
    else
    {
        // Since the range of possible Io type values is unbounded,
        // there's no way to guarantee a generic converter for any FromIoType
        // to a parameter of C++ IoObject*.  The solution is to only
        // return something as a FromIoType if it's a known type (and we
        // make sure to always add both the FromIoType converter and a
        // converter from that to IoObject).  Otherwise we don't know what
        // to do with the io_obj *anyway* so return it as a Term<IoObject*>
        // with the hope that it may get used as a C++ IoObject* parameter.
        // This enables IoObjects to be passed as C++ parameters, even if the
        // Io type of the object isn't among those blessed with other type convs.
        TypeIndex from_type = FromIoTypeInfo::create_index(get_type_name(io_obj));
        if (type_system->has_type(from_type))
            return create_expr(io_obj, from_type);
        else
            return Term<IoObject*>::create(io_obj);
    }
}

}}
