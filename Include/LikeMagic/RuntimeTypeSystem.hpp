// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
// 
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

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


    // Dummy type to represent SFMO collection methods
    struct SFMOCollection {};

    // Dummy type to represent an unregistered C++ class
    // (which may be the return value of a function)
    struct Unknown_CppObj {};

    StaticMethods functions;
    ProxyMethods proxy_methods;
    ProxyMethods collection_methods;

    template <typename T, bool is_copyable>
    typename boost::enable_if_c<is_copyable>::type
    register_copyable_conv()
    {
        // Allow pointers and references to be converted to value
        // only if the object is copyable.
        //add_conv<T*&, T, PtrDerefConv>();
        add_conv<T&, T>();
        //add_conv<T*&, T const, PtrDerefConv>();
    }

    template <typename T, bool is_copyable>
    typename boost::disable_if_c<is_copyable>::type
    register_copyable_conv()
    {
    }

    template <typename T, bool is_copyable>
    Class<T, is_copyable>& register_class_impl(std::string name)
    {
        BetterTypeInfo type = BetterTypeInfo::create<T>();
        if (classes.find(type) != classes.end())
        {
            return *dynamic_cast<Class<T, is_copyable>*>(classes[type]);
        }
        else
        {
            auto result = new LikeMagic::Marshaling::Class<T, is_copyable>(name, *this);
            result->add_base_abstr(&proxy_methods);

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
            //add_conv<T*&, T&, PtrDerefConv>();

            //add_conv<T*&, T const&, PtrDerefConv>();

            // enable pointer to value conversions only if class is copyable.
            register_copyable_conv<T, is_copyable>();

            classes[type.bare_type()] = result;

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
        if (!has_class(BetterTypeInfo::create<std::vector<T>>()))
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

    template <typename T, bool is_copyable=!boost::is_abstract<T>::value>
    Class<T, is_copyable>& register_class(std::string name)
    {
        //return check_for_collection<T, is_copyable>(name);
        return register_class_impl<T, is_copyable>(name);
    }

    StaticMethods& register_functions()
    {
        return functions;
    }
};

}
