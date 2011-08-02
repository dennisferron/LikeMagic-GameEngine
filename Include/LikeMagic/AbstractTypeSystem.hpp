// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/TypeConvGraph.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/GenericConv.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/SFMO/NullExpr.hpp"
#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/Utility/IsIterator.hpp"
#include "LikeMagic/SFMO/Trampoline.hpp"

#include "LikeMagic/Utility/TupleForEach.hpp"

#include "LikeMagic/Utility/KeyWrapper.hpp"
#include "LikeMagic/ITypeSystemObserver.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"

#include "boost/unordered_map.hpp"

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
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using namespace LikeMagic::TypeConv;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;


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

    //boost::unordered_map<TypeIndex, AbstractClass*> classes;
    std::vector<AbstractClass*> classes2;

    // Don't allow accidently making copies of this class
    AbstractTypeSystem(AbstractTypeSystem const&) = delete;
    AbstractTypeSystem & operator =(AbstractTypeSystem const&) = delete;

    void add_ptr_convs(TypeIndex index);

    template <typename From, typename To>
    void add_nochange_conv(TypeInfoPtr from, TypeInfoPtr to);

    template <typename From, typename To>
    void add_generic_conv(TypeInfoPtr from, TypeInfoPtr to);

    // handles const object or nonconst object.  T is either const void or just void.
    template <typename T>
    void add_conv_track(TypeInfoPtr type);

protected:

    AbstractTypeSystem();

    AbstractClass* unknown_class;

    TypeConvGraph conv_graph;

    std::set<ITypeSystemObserver*> observers;

public:

    void report();

    virtual ~AbstractTypeSystem();

    void print_type_graph() const;

    // These are used to turn off deletion of the C++ objects
    // to troubleshoot garbage collection issues.
    bool leak_memory() const;
    void set_leak_memory(bool flag);

    TypeInfoList get_registered_types() const;
    std::vector<std::string> get_base_names(TypeIndex type) const;
    std::string get_class_name(TypeIndex type) const;
    AbstractCppObjProxy* create_class_proxy(TypeIndex type) const;
    std::vector<std::string> const& get_method_names(TypeIndex type) const;
    AbstractCppObjProxy* call(TypeIndex type, std::string method_name, AbstractCppObjProxy* proxy, std::vector<ExprPtr> args) const;
    TypeInfoList get_arg_types(TypeIndex type, std::string method_name, int num_args) const;
    bool has_class(TypeIndex type) const;
    AbstractClass* get_class(TypeIndex type) const;
    void add_class(TypeIndex index, AbstractClass* class_ptr);

    void add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv);
    void add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv);

    template <typename From, typename To, template <typename From, typename To> class Converter=ImplicitConv>
    void add_conv()
    {
        add_converter_variations(
            BetterTypeInfo::create_index<From>(),
            BetterTypeInfo::create_index<To>(),
                new Converter<From, To>);
    }

    template <typename T>
    std::string get_class_name() const
    {
        static auto c_type = BetterTypeInfo::create_index<T>();
        return get_class_name(c_type);
    }

    ExprPtr try_conv(ExprPtr from_expr, TypeIndex to_type) const;
    bool has_conv(TypeIndex  from_type, TypeIndex to_type) const;

    template <typename To>
    bool has_conv(ExprPtr from) const
    {
        return has_conv(from->get_type(), BetterTypeInfo::create_index<To>());
    }

    template <typename To>
    boost::intrusive_ptr<Expression<To>> try_conv(ExprPtr from) const
    {
        return static_cast<Expression<To>*>(try_conv(from, BetterTypeInfo::create_index<To>()).get());
    }

    void add_type_system_observer(ITypeSystemObserver* observer);
    void register_base(LikeMagic::Marshaling::AbstractClass* class_, LikeMagic::Marshaling::AbstractClass const* base);
    void register_method(LikeMagic::Marshaling::AbstractClass* class_, std::string method_name, LikeMagic::CallTargets::AbstractCallTargetSelector* method);
    void print_conv_chain(TypeIndex from, TypeIndex to) const;

};

}
