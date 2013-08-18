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
#include "LikeMagic/Exprs/FalseExpr.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
#include "Iocaste/LikeMagicAdapters/IoObjectExpr.hpp"
#include "Iocaste/LikeMagicAdapters/FromIoTypeInfo.hpp"

#include "Iocaste/LikeMagicAdapters/IoListSTL.hpp"
#include "Iocaste/LikeMagicAdapters/IoVectorSTL.hpp"

#include "LikeMagic/AbstractTypeSystem.hpp"

#include <vector>
#include <algorithm>

using LikeMagic::Utility::BetterTypeInfo;
using namespace LikeMagic::TypeConv;

namespace Iocaste { namespace LikeMagicAdapters {

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




#define MKCONV(scriptType, cppType, ioFunc) \
{\
    struct From##scriptType : public AbstractTypeConverter \
    { \
        virtual ExprPtr wrap_expr(ExprPtr expr) const \
        { \
            boost::intrusive_ptr<IoObjectExpr> io_expr = static_cast<IoObjectExpr*>(expr.get()); \
            return Term<cppType>::create(ioFunc(io_expr->eval())); \
        } \
\
        virtual std::string description() const { return "From " #scriptType " Conv"; } \
    }; \
\
    type_system->add_converter_simple(FromIoTypeInfo::create_index(#scriptType), BetterTypeInfo::create_index<cppType&>(), new From##scriptType); \
}

void add_convs_from_script(AbstractTypeSystem& type_sys, IoVM* iovm)
{
    // Nil requires special handling because it produces not a term but a NullExpr.
    struct FromNil : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            return NullExpr::create();
        }

        virtual std::string description() const { return "From Nil Conv"; }
    };
    static const char* name1 = "Nil";
    static std::string name2(name1);
    static auto from_type(FromIoTypeInfo::create_index(name2));
    auto to_type = FromNil().wrap_expr(0)->get_type();
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
    };
    type_system->add_converter_simple(FromIoTypeInfo::create_index("Nil"), BetterTypeInfo::create_index<bool>(), new FromNilToFalse);

    // Allow nil to convert to void (for IoBlock eval<void>)
    struct FromNilToVoid : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            return 0;
        }

        virtual std::string description() const { return "From Nil to void Conv"; }
    };
    type_system->add_converter_simple(FromIoTypeInfo::create_index("Nil"), BetterTypeInfo::create_index<void>(), new FromNilToVoid);


    // IoBlock requires an extra argument (type_sys)
    struct FromIoBlock : public AbstractTypeConverter
    {
        IoVM* iovm;
        FromIoBlock(IoVM* iovm_) : iovm(iovm_) {}

        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            boost::intrusive_ptr<IoObjectExpr> io_expr = static_cast<IoObjectExpr*>(expr.get());
            IoObject* io_obj = io_expr->eval();
            return Term<IoBlock>::create(iovm, io_obj, io_obj);
        }

        virtual std::string description() const { return "From Block Conv"; }
    };

    type_system->add_converter_simple(FromIoTypeInfo::create_index("Block"), BetterTypeInfo::create_index<IoBlock&>(), new FromIoBlock(type_sys, iovm));

    MKCONV(Number, double, IoNumber_asDouble)
    MKCONV(Number, int, IoNumber_asInt)
    MKCONV(Number, unsigned int, IoNumber_asInt)
    MKCONV(Number, short, (short)IoNumber_asInt)
    MKCONV(Number, unsigned char, (unsigned char)IoNumber_asInt)
    MKCONV(Number, float, IoNumber_asFloat)
    MKCONV(Sequence, std::string, IoSeq_asCString)
    //MKCONV(Bool, bool, ISTRUE)

    struct FromBool : public AbstractTypeConverter
    {
        virtual ExprPtr wrap_expr(ExprPtr expr) const
        {
            boost::intrusive_ptr<IoObjectExpr> io_expr = static_cast<IoObjectExpr*>(expr.get());
            bool value = ISTRUE(io_expr->eval());
            boost::intrusive_ptr<Expression<bool&>> result = Term<bool>::create(value);
            return result;
        }

        virtual std::string description() const { return "From Bool Conv"; }
    };

    type_system->add_converter_simple(FromIoTypeInfo::create_index("Bool"), BetterTypeInfo::create_index<bool&>(), new FromBool);


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
    static TypeIndex wants_io_obj = BetterTypeInfo::create_index<IoObject*>();

    if (is_Exprs_obj(io_obj) && !(to_type == wants_io_obj))
    {
        AbstractCppObjProxy* proxy(
                reinterpret_cast<AbstractCppObjProxy*>
                    (IoObject_dataPointer(io_obj)));
        proxy->check_magic();
        return proxy->get_expr();
    }
    else
    {
        return IoObjectExpr::create(io_obj);
    }
}

}}
