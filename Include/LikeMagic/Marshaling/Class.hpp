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

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;

template <typename T, bool is_copyable>
class Class : public AbstractClass
{
private:

    // No unnamed Class, no passing Class copies around.
    Class();
    Class(const Class&);

    friend class LikeMagic::RuntimeTypeSystem;
    Class(std::string name_, RuntimeTypeSystem& type_system_) : AbstractClass(name_, type_system_)
    {
    }

public:

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
        auto calltarget = new ConstructorCallTarget<T, is_copyable, Args...>(type_system);
        add_method(method_name, calltarget);
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