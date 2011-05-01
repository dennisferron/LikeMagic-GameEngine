// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractClass.hpp"
//#include "CallTargetSelector.hpp"
#include "LikeMagic/Marshaling/MethodCallGenerator.hpp"
#include "ConstructorCallTarget.hpp"
#include "DestructorCallTarget.hpp"
#include "LikeMagic/TypeConv/NumberConv.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/BaseConv.hpp"
#include "LikeMagic/TypeConv/AddrOfConv.hpp"

#include "FieldGetterTarget.hpp"
#include "FieldSetterTarget.hpp"
#include "FieldReferenceTarget.hpp"
#include "ArrayFieldGetterTarget.hpp"
#include "ArrayFieldSetterTarget.hpp"
#include "ArrayFieldReferenceTarget.hpp"
#include "CustomFieldGetterTarget.hpp"
#include "CustomFieldSetterTarget.hpp"

#include "LikeMagic/SFMO/ClassExpr.hpp"

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;


/*
"In the same way, when using the machine up in the attic in the early days,
I was solving one problem after another after another; a fair number were
successful and there were a few failures. I went home one Friday after
finishing a problem, and curiously enough I wasn't happy; I was depressed.
I could see life being a long sequence of one problem after another
after another. After quite a while of thinking I decided, ``No, I should
be in the mass production of a variable product. I should be concerned
with all of next year's problems, not just the one in front of my face.''
    -- Richard Hamming, "You and Your Research."
*/

template <typename T, bool is_copyable>
class Class : public AbstractClass
{
private:

    // No unnamed Class, no passing Class copies around, no assignment.
    Class();
    Class(const Class&);
    Class& operator =(const Class&);

    friend class LikeMagic::RuntimeTypeSystem;
    Class(std::string name_, AbstractTypeSystem& type_system_) : AbstractClass(name_, type_system_)
    {
    }

    // Utility function for generating alternate constructor names.
    static std::string alt_name(std::string prefix, std::string method_name)
    {
        if (method_name.substr(0, 3) == "new")
            return prefix + method_name.substr(3);
        else
            return prefix + "_" + method_name;
    }

    // Utility function for declaring various different types of constructor call targets.
    template <typename ConstructedObjT, typename... Args>
    void add_constructor(std::string prefix, std::string method_name)
    {
        auto target = new ConstructorCallTarget<ConstructedObjT, is_copyable, Args...>(type_system);
        add_method(alt_name(prefix, method_name), target);
    }

public:

    virtual TypeIndex get_type() const { return BetterTypeInfo::create_index<T>(); }

    virtual AbstractCppObjProxy* create_class_proxy() const
    {
        return
            // Return as call by reference, not call by value, in case type is not copyable.
            // It doesn't matter whether we use call by reference or
            // call by pointer, because LikeMagic supports both.
            CppObjProxy<T&, is_copyable>::create
            (
                ClassExpr<T&>::create(),
                type_system
            );
    }

    template <typename Base, bool base_is_copyable, template <typename From, typename To> class Converter=BaseConv>
    void add_base(Class<Base, base_is_copyable> const& base_class)
    {
        add_base_abstr(&base_class);

        type_system.add_conv<T&, Base&, Converter>();
        type_system.add_conv<T*, Base*, Converter>();

        //type_system.add_conv<T&, Base const&, Converter>();
        //type_system.add_conv<T const&, Base const&, Converter>();

        // Autoconvert references into base pointers (so we can pass Term objects by pointer)
//        type_system.add_conv<T&, Base*, AddrOfConv>();
//        type_system.add_conv<T&, Base const*, AddrOfConv>();
//        type_system.add_conv<T const&, Base const*, AddrOfConv>();
//
//        type_system.add_conv<T*, Base*, Converter>();
//        type_system.add_conv<T*, Base const*, Converter>();
//        type_system.add_conv<T const*, Base const*, Converter>();
//
//        type_system.add_conv<T*&, Base*, Converter>();
//        type_system.add_conv<T*&, Base const*, Converter>();
//        type_system.add_conv<T const*&, Base const*, Converter>();
    }

    // Use this to declare methods of your C++ class callable from script.
    template <typename F>
    void bind_method(std::string method_name, F f)
    {
        //auto calltarget = new CallTargetSelector<MethodCallGenerator, T, F>(f, type_system);
        auto calltarget = new MethodCallGenerator<T, F>(f, type_system);
        add_method(method_name, calltarget);
    }

    // A "hack" to allow binding static class methods without using class StaticMethods::bind_method.
    template <typename F>
    void bind_static_method(std::string method_name, F f)
    {
        auto calltarget = new MethodCallGenerator<T, F, true, false>(f, type_system);
        add_method(method_name, calltarget);
    }

    // A further "hack" to allow binding nonmember operators.  Target object gets converted to first function argument.
    template <typename F>
    void bind_nonmember_op(std::string method_name, F f)
    {
        auto calltarget = new MethodCallGenerator<T, F, true, true>(f, type_system);
        add_method(method_name, calltarget);
    }

    template <typename... Args>
    void bind_constructor(std::string method_name="new")
    {
        // When the object is created under the name of "new", it is a resource
        // and must be deleted when you are finished with it.
        add_constructor<T*, Args...>("new", method_name);

        // Alternate constructors - tmp, ref, ptr

        // Create the value type / temp objects version of the constructor.
        // This one stores the value directly in the term.
        add_constructor<T, Args...>("tmp", method_name);

        // This version creates the object by reference.  It actually also creates
        // a value-type Term to hold the object, but wraps that in a Reference expression.
        // This prevents to-script conversion from occuring, allowing you to e.g. get a true int&
        // that doesn't get converted to a script Number type.
        add_constructor<T&, Args...>("ref", method_name);

        // This version creates an empty (NULL) pointer without new'ing an object.
        // It can be used to create something suitable for passing to C++ functions that
        // return a result by writing to a reference-to-pointer arg.
        // Note: there's no args for this construction method.
        if (!has_method(alt_name("ptr", method_name), 0))
        add_constructor<T*&>("ptr", method_name);
    }

    // Use this to bind fields.
    template <typename F>
    void bind_field(std::string field_name, F f)
    {
        auto setter = new FieldSetterTarget<T, F>(f, type_system);
        add_method("set_" + field_name, setter);
        auto getter = new FieldGetterTarget<T, F>(f, type_system);
        add_method("get_" + field_name, getter);
        auto reffer = new FieldReferenceTarget<T, F>(f, type_system);
        add_method("ref_" + field_name, reffer);
    }

    // Use this to bind fields.
    template <typename F>
    void bind_array_field(std::string field_name, F f)
    {
        auto setter = new ArrayFieldSetterTarget<T, F>(f, type_system);
        add_method("set_" + field_name, setter);
        auto getter = new ArrayFieldGetterTarget<T, F>(f, type_system);
        add_method("get_" + field_name, getter);
        auto reffer = new ArrayFieldReferenceTarget<T, F>(f, type_system);
        add_method("ref_" + field_name, reffer);
    }

    // Use this to bind fields.
    template <typename FieldAccessor>
    void bind_custom_field(std::string field_name, FieldAccessor f)
    {
        //auto setter = new CallTargetSelector<CustomFieldSetterTarget, T, FieldAccessor>(f, type_system);
        auto setter = new CustomFieldSetterTarget<T, FieldAccessor>(f, type_system);
        add_method("set_" + field_name, setter);
        //auto getter = new CallTargetSelector<CustomFieldGetterTarget, T, FieldAccessor>(f, type_system);
        auto getter = new CustomFieldGetterTarget<T, FieldAccessor>(f, type_system);
        add_method("get_" + field_name, getter);
    }

    void bind_delete()
    {
        // In C++, any type can be deleted.
        auto deleter = new DestructorCallTarget<T>(type_system);
        add_method("delete", deleter);
    }

};


}}
