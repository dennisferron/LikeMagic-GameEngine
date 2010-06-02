#pragma once

#include "AbstractClass.hpp"
#include "CallTargetSelector.hpp"
#include "ConstructorCallTarget.hpp"
#include "LikeMagic/TypeConv/NumberConv.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/BaseConv.hpp"
#include "LikeMagic/TypeConv/AddrOfConv.hpp"

#include "FieldGetterTarget.hpp"
#include "FieldSetterTarget.hpp"
#include "ArrayFieldGetterTarget.hpp"
#include "ArrayFieldSetterTarget.hpp"
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

public:

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
        type_system.add_conv<T&, Base const&, Converter>();
        type_system.add_conv<T const&, Base const&, Converter>();

        // Autoconvert references into base pointers (so we can pass Term objects by pointer)
        type_system.add_conv<T&, Base*, AddrOfConv>();
        type_system.add_conv<T&, Base const*, AddrOfConv>();
        type_system.add_conv<T const&, Base const*, AddrOfConv>();

        type_system.add_conv<T*, Base*, Converter>();
        type_system.add_conv<T*, Base const*, Converter>();
        type_system.add_conv<T const*, Base const*, Converter>();

        type_system.add_conv<T*&, Base*, Converter>();
        type_system.add_conv<T*&, Base const*, Converter>();
        type_system.add_conv<T const*&, Base const*, Converter>();
    }

    // Use this to declare methods of your C++ class callable from script.
    template <typename F>
    void bind_method(std::string method_name, F f)
    {
        auto calltarget = new CallTargetSelector<MethodCallGenerator, T, F>(f, type_system);
        add_method(method_name, calltarget);
    }

    template <typename... Args>
    void bind_constructor(std::string method_name="new")
    {
        // When the object is created under the name of "new", it is a resource
        // and must be deleted when you are finished with it.
        auto resources = new ConstructorCallTarget<T*, is_copyable, Args...>(type_system);
        add_method(method_name, resources);

        // Convert the "newXXXX" method name to "tmpXXXX" for temporary objects.
        std::string temps_name;
        if (method_name.substr(0, 3) == "new")
            temps_name = "tmp" + method_name.substr(3);
        else
            temps_name = "tmp_" + method_name;

        // Create the temp objects version of the constructor.
        // This one stores the value directly in the term.
        auto temps = new ConstructorCallTarget<T, is_copyable, Args...>(type_system);
        add_method(temps_name, temps);
    }

    // Use this to bind fields.
    template <typename F>
    void bind_field(std::string field_name, F f)
    {
        auto setter = new CallTargetSelector<FieldSetterTarget, T, F>(f, type_system);
        add_method("set_" + field_name, setter);
        auto getter = new CallTargetSelector<FieldGetterTarget, T, F>(f, type_system);
        add_method("get_" + field_name, getter);
    }

    // Use this to bind fields.
    template <typename F>
    void bind_array_field(std::string field_name, F f)
    {
        auto setter = new CallTargetSelector<ArrayFieldSetterTarget, T, F>(f, type_system);
        add_method("set_" + field_name, setter);
        auto getter = new CallTargetSelector<ArrayFieldGetterTarget, T, F>(f, type_system);
        add_method("get_" + field_name, getter);
    }

    // Use this to bind fields.
    template <typename FieldAccessor>
    void bind_custom_field(std::string field_name, FieldAccessor f)
    {
        auto setter = new CallTargetSelector<CustomFieldSetterTarget, T, FieldAccessor>(f, type_system);
        add_method("set_" + field_name, setter);
        auto getter = new CallTargetSelector<CustomFieldGetterTarget, T, FieldAccessor>(f, type_system);
        add_method("get_" + field_name, getter);
    }

};


}}
