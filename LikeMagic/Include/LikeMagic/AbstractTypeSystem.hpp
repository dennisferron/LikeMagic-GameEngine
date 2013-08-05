// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
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
#include "LikeMagic/Exprs/NullExpr.hpp"
#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/Utility/IsIterator.hpp"
#include "LikeMagic/Exprs/Trampoline.hpp"

#include "LikeMagic/Utility/TupleForEach.hpp"

#include "LikeMagic/Utility/KeyWrapper.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"

#include "boost/unordered_map.hpp"

#include <map>
#include <stdexcept>
#include <string>

namespace LikeMagic {

namespace Exprs {
    class AbstractCppObjProxy;
}

namespace Marshaling {
    class AbstractMethodset;
    class TypeMirror;
}

using LikeMagic::Marshaling::AbstractMethodset;
using LikeMagic::Marshaling::TypeMirror;
using LikeMagic::Utility::BetterTypeInfo;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::TypeInfoList;
using namespace LikeMagic::TypeConv;
using namespace LikeMagic::Exprs;
using namespace LikeMagic::Utility;


// The reason why TypeSystem is split into AbstractTypeSystem and
// the concrete RuntimeTypeSystem is that things like class Class
// need to access type system methods, but type system methods in
// turn need to create Class objects, creating a circular dependency.
// One way to break the dependency is to make Class use the abstract
// interface instead of giving it direct access to RuntimeTypeSystem.
// The Factory Pattern is no help here because RuntimeTypeSystem must
// create concrete Class instantiations, not TypeMirror, so it
// would still have needed to include Class.hpp even if it used a factory.


class AbstractTypeSystem
{
private:
    // This is used for debugging.
    bool leak_memory_flag;

    //boost::unordered_map<TypeIndex, TypeMirror*> classes;
    std::vector<TypeMirror*> classes2;

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

    TypeMirror* unknown_class;

    TypeConvGraph conv_graph;

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
    ExprPtr create_class_expr(TypeIndex type) const;
    std::vector<std::string> const& get_method_names(TypeIndex type) const;
    TypeInfoList get_arg_types(TypeIndex type, std::string method_name, int num_args) const;
    bool has_class(TypeIndex type) const;
    TypeMirror* get_class(TypeIndex type) const;
    void add_class(TypeIndex index, TypeMirror* class_ptr);

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

    void register_base(LikeMagic::Marshaling::TypeMirror* class_, LikeMagic::Marshaling::TypeMirror const* base);
    void register_method(LikeMagic::Marshaling::TypeMirror* class_, std::string method_name, LikeMagic::CallTargets::AbstractMethod* method);
    void print_conv_chain(TypeIndex from, TypeIndex to) const;

    void add_ptr_conversions(TypeIndex from_type, bool auto_deref);
};

// The global type_system variable needs to be a pointer (not a reference)
// so that in situations where linking doesn't properly resolve the symbol
// to the same location (this can happen, e.g., with DLLs on Windows)
// then we can use an assignment to the pointer to reconcile the two.
// Or, at worst, the uninitialized copy of the pointer variable will
// be null, which is a problem much easier to diagnose than a situation
// in which two different copies of the actual object exist by accident.
extern AbstractTypeSystem* type_system;
}
