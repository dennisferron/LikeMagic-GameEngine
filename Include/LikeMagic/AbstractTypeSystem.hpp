#pragma once

#include "LikeMagic/TypeConv/TypeConvGraph.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/SFMO/NullExpr.hpp"
#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/Utility/IsIterator.hpp"
#include "LikeMagic/Utility/StripConst.hpp"
#include "LikeMagic/SFMO/Trampoline.hpp"

#include "LikeMagic/Utility/TupleForEach.hpp"

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>

#include <map>
#include <stdexcept>
#include <string>

namespace LikeMagic {

namespace SFMO {
    class AbstractCppObjProxy;
}

namespace Marshaling {
    class AbstractMethodset;
    class AbstractClass;
}

using LikeMagic::Marshaling::AbstractMethodset;
using LikeMagic::Marshaling::AbstractClass;
using LikeMagic::Utility::BetterTypeInfo;
using namespace LikeMagic::TypeConv;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;


template <typename T, bool is_abstract=boost::is_abstract<T>::value>
struct DoConv
{
    static ExprPtr cref_to_value(ExprPtr from)
    {
        return Trampoline<T const&, T, ImplicitConvImpl<T const&, T>>::create(from);
    }

    static ExprPtr value_to_cref(ExprPtr from)
    {
        return Trampoline<T, T const&, ImplicitConvImpl<T, T const&>>::create(from);
    }
};

template <typename T>
struct DoConv<T, true>
{
    static ExprPtr cref_to_value(ExprPtr from)
    {
        throw std::logic_error("Cannot convert " + BetterTypeInfo::create<T>().describe() + " from const ref to value; the type is abstract.");
    }

    static ExprPtr value_to_cref(ExprPtr from)
    {
        throw std::logic_error("Cannot convert " + BetterTypeInfo::create<T>().describe() + " from value to const ref; the type is abstract.");
    }
};


// The reason why TypeSystem is split into AbstractTypeSystem and
// the concrete RuntimeTypeSystem is that things like class Class
// need to access type system methods, but type system methods in
// turn need to create Class objects, creating a circular dependency.
// One way to break the dependency is to make Class use the abstract
// interface instead of giving it direct access to RuntimeTypeSystem.
// The Factory Pattern is no help here because RuntimeTypeSystem must
// create concrete Class instantiations, not AbstractClass, so it
// would still have needed to include Class.hpp even if it used a factory.


class AbstractTypeSystem
{
private:
    // This is used for debugging.
    bool leak_memory_flag;

    ExprPtr search_for_conv(ExprPtr from, BetterTypeInfo from_type, BetterTypeInfo to_type) const;

    bool is_ref_to_value_conv(BetterTypeInfo from_type, BetterTypeInfo to_type) const;
    bool is_value_to_ref_conv(BetterTypeInfo from_type, BetterTypeInfo to_type) const;
    bool is_nullptr_conv(ExprPtr from, BetterTypeInfo to_type) const;
    bool is_const_adding_conv(BetterTypeInfo from_type, BetterTypeInfo to_type) const;


    template <typename To>
    ExprPtr try_conv_impl(ExprPtr from) const
    {
        std::string error_msg_header = "try_conv from " + from->get_type().describe() + " to " + BetterTypeInfo::create<To>().describe() + ": ";

        BetterTypeInfo from_type = from->get_type();
        BetterTypeInfo to_type = BetterTypeInfo::create<To>();

        typedef typename boost::remove_reference<typename boost::remove_const<To>::type>::type BareTo;

        // Don't need to rely on the type converter if no conversion is needed.
        // Or can we simply add const modifiers to from_type?
        if (from_type == to_type || is_const_adding_conv(from_type, to_type))
        {
            return from;
        }
        // Can convert NULL to any pointer type.
        else if (is_nullptr_conv(from, to_type))
        {
            return make_nullexpr<To>();
        }
        // Reference to value
        else if (is_ref_to_value_conv(from_type, to_type))
        {
            return DoConv<BareTo>::cref_to_value(from);
        }
        // value to const ref
        else if (is_value_to_ref_conv(from_type, to_type))
        {
            return DoConv<BareTo>::value_to_cref(from);
        }
        // Else need a type converter
        else
        {
            return search_for_conv(from, from_type, to_type);
        }
    }

    // Functor used with tuple_for_each_pair_in_seq by make_conv_chain
    struct ConvChainBuilder;
    friend struct ConvChainBuilder;
    struct ConvChainBuilder
    {
        AbstractTypeSystem const& type_sys;
        ExprPtr expr;

        ConvChainBuilder(AbstractTypeSystem const& type_sys_, ExprPtr expr_)
            : type_sys(type_sys_), expr(expr_) {}

        void operator()(BetterTypeInfo from_type, BetterTypeInfo to_type)
        {
            // "decorate" the existing expression with the next conversion, and store it in place of existing one.
            expr = type_sys.get_converter(from_type, to_type)->wrap_expr(expr);
        }
    };

    template <typename... T>
    ExprPtr make_conv_chain(ExprPtr from, std::tuple<T...> types) const
    {
        ConvChainBuilder f(*this, from);
        tuple_for_each_pair_in_seq(f, types);
        return f.expr;
    }

protected:

    AbstractTypeSystem();

    std::map<BetterTypeInfo, AbstractClass*> classes;
    AbstractClass const* unknown_class;

    typedef std::map<BetterTypeInfo,
                std::map<BetterTypeInfo,
                    AbstractTypeConverter const*>> ConvMap;

    ConvMap converters;

    TypeConvGraph conv_graph;

    bool has_converter(BetterTypeInfo from, BetterTypeInfo to) const;
    AbstractTypeConverter const* get_converter(BetterTypeInfo from, BetterTypeInfo to) const;

    bool has_class(BetterTypeInfo type) const;
    AbstractClass const* get_class(BetterTypeInfo type) const;

public:

    virtual ~AbstractTypeSystem() {}

    void print_type_graph() const;

    // These are used to turn off deletion of the C++ objects
    // to troubleshoot garbage collection issues.
    bool leak_memory() const;
    void set_leak_memory(bool flag);

    std::vector<BetterTypeInfo> get_registered_types() const;
    std::vector<std::string> get_base_names(BetterTypeInfo type) const;
    std::string get_class_name(BetterTypeInfo type) const;
    AbstractCppObjProxy* create_class_proxy(BetterTypeInfo type) const;
    std::vector<std::string> const& get_method_names(BetterTypeInfo type) const;
    AbstractCppObjProxy* call(BetterTypeInfo type, std::string method_name, AbstractCppObjProxy* proxy, std::vector<ExprPtr> args) const;
    std::vector<BetterTypeInfo> get_arg_types(BetterTypeInfo type, std::string method_name, int num_args) const;

    void add_converter(BetterTypeInfo from, BetterTypeInfo to, AbstractTypeConverter const* conv);

    template <typename From, typename To, template <typename From, typename To> class Converter=ImplicitConv>
    void add_conv()
    {
        add_converter(
            BetterTypeInfo::create<From>(),
            BetterTypeInfo::create<To>(),
                new Converter<From, To>);
    }

    template <typename T>
    std::string get_class_name() const
        { return get_class_name(BetterTypeInfo::create<T>()); }

    template <typename To>
    boost::intrusive_ptr<Expression<To>> try_conv(ExprPtr from) const
    {
        return reinterpret_cast<Expression<To>*>(try_conv_impl<To>(from).get());
    }

    private:
        template <typename To>
            static typename boost::enable_if<boost::is_pointer<To>,
                typename boost::intrusive_ptr<Expression<To>>>::type
        make_nullexpr()
        {
            return NullExpr<To>::create();
        }

        template <typename To>
            static typename boost::disable_if<boost::is_pointer<To>,
                typename boost::intrusive_ptr<Expression<To>>>::type
        make_nullexpr()
        {
            throw std::logic_error("Tried to convert NULL value to nonpointer type "
                    + LikeMagic::Utility::TypeDescr<To>::text());
        }

};

}
