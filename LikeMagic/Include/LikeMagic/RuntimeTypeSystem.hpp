// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
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
#include "LikeMagic/Marshaling/NamespaceTypeInfo.hpp"
#include "LikeMagic/TypeConv/NumberConv.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/VectorConv.hpp"
#include "LikeMagic/TypeConv/AddrOfConv.hpp"
#include "LikeMagic/TypeConv/PtrDerefConv.hpp"
#include "LikeMagic/TypeConv/PtrCastConv.hpp"
#include "LikeMagic/CallTargets/ClassExprTarget.hpp"

#if defined(USE_DLL_BUILD) && (defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__)
  #ifdef BUILDING_DLL_STD_BINDINGS
    #ifdef __GNUC__
      #define DLL_PUBLIC_RUNTIME_TYPE_SYSTEM __attribute__((dllexport))
    #else
      #define DLL_PUBLIC_RUNTIME_TYPE_SYSTEM __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC_RUNTIME_TYPE_SYSTEM __attribute__((dllimport))
    #else
      #define DLL_PUBLIC_RUNTIME_TYPE_SYSTEM __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC_RUNTIME_TYPE_SYSTEM __attribute__ ((visibility("default")))
    #define DLL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define DLL_PUBLIC_RUNTIME_TYPE_SYSTEM
    #define DLL_LOCAL
  #endif
#endif

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
// create concrete Class instantiations, not TypeMirror, so it
// would still have needed to include Class.hpp even if it used a factory.

class RuntimeTypeSystem : public AbstractTypeSystem
{
protected:

    TypeInfoCache* dll_shared_typeinfo;

    // Used for a type index for proxy methods.  Don't want to use AbstractCppObjProxy
    // because we might actually want to bind methods to it later.
    struct ProxyMethodsType {};

    // Dummy type to represent an unregistered C++ class
    // (which may be the return value of a function)
    struct Unknown_CppObj {};

    template <typename T, bool is_copyable>
    typename boost::enable_if_c<is_copyable>::type
    register_copyable_conv()
    {
        add_conv<T const&, T>();
    }

    template <typename T, bool is_copyable>
    typename boost::disable_if_c<is_copyable>::type
    register_copyable_conv()
    {
    }

protected:

    RuntimeTypeSystem();

public:

    // Important:  you must set the type info cache instances in all your DLLs to this pointer.
    TypeInfoCache* get_typeinfo_cache() { return dll_shared_typeinfo; }

    template <typename T, bool is_copyable=!boost::is_abstract<T>::value, bool add_deref_ptr_conv=true>
    TypeMirror& register_class(std::string name, TypeMirror& namespace_)
    {
        static TypeIndex type(BetterTypeInfo::create_index<T>());
        namespace_.add_method(name, new ClassExprTarget<T>());
        if (has_class(type))
        {
            return *get_class(type);
        }
        else
        {
            auto result = new LikeMagic::Marshaling::TypeMirror(name, *this, ns);
            add_class(type, result);
            result->add_base_abstr(proxy_methods);
            add_ptr_conversions(type, add_deref_ptr_conv);
            register_copyable_conv<T, is_copyable>();
            bind_built_in_operations<T>(*result);
            add_delegate_conv<T>();
            return *result;
        }
    }

    template <typename T>
    TypeMirror& register_enum(std::string name, TypeMirror& namespace_)
    {
        auto& result = register_class<T, true>(name, ns);
        result.bind_nonmember_op("==",    &EnumHelper<T>::equals);
        result.bind_nonmember_op("!=",    &EnumHelper<T>::not_equals);
        result.bind_nonmember_op("value", &EnumHelper<T>::value);
        result.bind_nonmember_op("asString", &EnumHelper<T>::asString);
        namespace_.add_method(name, new ClassExprTarget<T>());
        return result;
    }

    TypeMirror global_namespace();
};

}
