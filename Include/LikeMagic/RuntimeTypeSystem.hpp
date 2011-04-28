// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/type_traits/is_enum.hpp"
#include "LikeMagic/Utility/EnumHelper.hpp"

#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/Marshaling/Class.hpp"
#include "LikeMagic/Marshaling/StaticMethods.hpp"
#include "LikeMagic/Marshaling/ProxyMethods.hpp"
#include "LikeMagic/TypeConv/NumberConv.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/VectorConv.hpp"
#include "LikeMagic/TypeConv/AddrOfConv.hpp"
#include "LikeMagic/TypeConv/PtrDerefConv.hpp"

namespace LikeMagic {

using namespace LikeMagic::Marshaling;

using LikeMagic::Utility::TypeIndex;
using LikeMagic::Utility::EnumHelper;

// The reason why TypeSystem is split into AbstractTypeSystem and
// the concrete RuntimeTypeSystem is that things like class Class
// need to access type system methods, but type system methods in
// turn need to create Class objects, creating a circular dependency.
// One way to break the dependency is to make Class use the abstract
// interface instead of giving it direct access to RuntimeTypeSystem.
// The Factory Pattern is no help here because RuntimeTypeSystem must
// create concrete Class instantiations, not AbstractClass, so it
// would still have needed to include Class.hpp even if it used a factory.

class RuntimeTypeSystem : public AbstractTypeSystem
{
private:
    TypeInfoCache* dll_shared_typeinfo;

    // Dummy type to represent SFMO collection methods
    struct SFMOCollection {};

    // Dummy type to represent an unregistered C++ class
    // (which may be the return value of a function)
    struct Unknown_CppObj {};

    StaticMethods* functions;
    ProxyMethods* proxy_methods;
    ProxyMethods* collection_methods;

    template <typename T, bool is_copyable>
    typename boost::enable_if_c<is_copyable>::type
    register_copyable_conv()
    {
        // Allow pointers and references to be converted to value
        // only if the object is copyable.
        //add_conv<T*&, T, PtrDerefConv>();
        add_conv<T&, T>();
        add_conv<T const&, T>();
        //add_conv<T*&, T const, PtrDerefConv>();
    }

    template <typename T, bool is_copyable>
    typename boost::disable_if_c<is_copyable>::type
    register_copyable_conv()
    {
    }


    template <typename T, bool is_copyable>
    typename boost::enable_if<boost::is_enum<T>>::type
    register_enum(Class<T, is_copyable>& result)
    {
        result.bind_nonmember_op("==",    &EnumHelper<T>::equals);
        result.bind_nonmember_op("!=",    &EnumHelper<T>::not_equals);
        result.bind_nonmember_op("value", &EnumHelper<T>::value);
    }

    template <typename T, bool is_copyable>
    typename boost::disable_if<boost::is_enum<T>>::type
    register_enum(Class<T, is_copyable>& result)
    {
    }


    template <typename T, bool is_copyable>
    Class<T, is_copyable>& register_class_impl(std::string name)
    {
        static_assert(boost::is_same<T, typename LikeMagic::Utility::StripModifiers<T>::strip::type>::value, "Can only register bare types as classes.");

        static TypeIndex type(BetterTypeInfo::create_index<T>());
        if (has_class(type))
        {
            return *dynamic_cast<Class<T, is_copyable>*>(get_class(type));
        }
        else
        {
            auto result = new LikeMagic::Marshaling::Class<T, is_copyable>(name, *this);
            add_class(type, result);

            result->add_base_abstr(proxy_methods);
            result->bind_delete();

            // If the user wants to give their class collection_methods, let them do it via an API function!
            //if (IsContainer<T>::value)
            //    result->add_base_abstr(&collection_methods);

            // Allow passing the actual object to things that need the pointer to the object.
            add_conv<T&, T*, AddrOfConv>();
            //add_conv<T&, T const*, AddrOfConv>();
            //add_conv<T const&, T const*, AddrOfConv>();

            // Also allow converting pointers back to references.
            add_conv<T*, T&, PtrDerefConv>();
            //add_conv<T*, T const&, PtrDerefConv>();

            // References to pointers can be converted to pointers.
            add_conv<T*&, T*>();
            add_conv<T* const&, T*>();
            //add_conv<T*&, T&, PtrDerefConv>();

            //add_conv<T*&, T const&, PtrDerefConv>();

            // enable pointer to value conversions only if class is copyable.
            register_copyable_conv<T, is_copyable>();

            // Add enum-specific things if applicable.
            register_enum<T, is_copyable>(*result);

            return *result;
        }
    }

    /*
     *
     * These three functions were part of a feature that is not used at this moment.
     * They were slowing down build times.
     * When the feature is re-enabled, most likely I'll have the user manually
     * register classes they want to use this with, rather than registering all classes this way.

    template <typename T>
    void register_collection(std::string name)
    {
        if (!has_class(BetterTypeInfo::create_index<std::vector<T>>()))
        {
            auto& collection = register_class_impl<std::vector<T>, true>("vector_of_" + name);
            collection.template bind_constructor<>();
            collection.add_base_abstr(&collection_methods);
            collection.template bind_method<
                void (std::vector<T>::*)(const T&)>("push_back", &std::vector<T>::push_back);
            collection.bind_method("size", &std::vector<T>::size);

            // make the collection convertible to a pointer.
            add_conv<std::vector<T>&, T*, VectorConv>();
            add_conv<std::vector<T>&, T const*, VectorConv>();
            add_conv<std::vector<T> const&, T const*, VectorConv>();
        }
    }

    template <typename T, bool is_copyable>
    typename boost::enable_if_c<
        is_copyable && !boost::is_same<T, bool>::value, Class<T, is_copyable>&
    >::type
    check_for_collection(std::string name)
    {
        // T is copyable so register a collection of it.  TODO:  default constructible???
        register_collection<T>(name);

        return register_class_impl<T, is_copyable>(name);
    }

    template <typename T, bool is_copyable>
    typename boost::disable_if_c<
        is_copyable && !boost::is_same<T, bool>::value, Class<T, is_copyable>&
    >::type
    check_for_collection(std::string name)
    {
        return register_class_impl<T, is_copyable>(name);
    }

    */

public:

    RuntimeTypeSystem();

    // Important:  you must set the type info cache instances in all your DLLs to this pointer.
    TypeInfoCache* get_typeinfo_cache() { return dll_shared_typeinfo; }

    template <typename T, bool is_copyable=!boost::is_abstract<T>::value>
    Class<T, is_copyable>& register_class(std::string name)
    {
        //return check_for_collection<T, is_copyable>(name);
        auto& result = register_class_impl<T, is_copyable>(name);

        return result;
    }

    // Currently register_class is capable of discerning enums.
    template <typename T>
    Class<T, true>& register_enum(std::string name)
    {
        auto& result = register_class_impl<T, true>(name);

        //result.bind_nonmember_op("==",    &EnumHelper<T>::equals);
        //result.bind_nonmember_op("!=",    &EnumHelper<T>::not_equals);
        //result.bind_nonmember_op("value", &EnumHelper<T>::value);

        result.bind_nonmember_op("asString", &EnumHelper<T>::asString);

        return result;
    }

    StaticMethods& register_functions()
    {
        return *functions;
    }

};

}
