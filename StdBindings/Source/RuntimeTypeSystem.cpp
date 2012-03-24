// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/StdBindings/StdBindings.hpp"

#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "LikeMagic/NamespacePath.hpp"

#include "LikeMagic/TypeConv/StringConv.hpp"
#include "LikeMagic/TypeConv/IteratorConv.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"

#include "boost/preprocessor/seq/for_each.hpp"

#include "LikeMagic/ScriptUtil.hpp"

#include <sstream>

#define add_num_conv(type) \
add_conv<type, type const&, NumberConv>(); \
add_conv<type&, type, NumberConv>(); \
add_conv<type const&, type, NumberConv>(); \
/* \
add_conv<double, type, NumberConv>(); \
add_conv<double, type const&, NumberConv>(); \
add_conv<double&, type, NumberConv>(); \
add_conv<double&, type const&, NumberConv>(); \
add_conv<double const&, type, NumberConv>(); \
add_conv<double const&, type const&, NumberConv>(); */ \
add_conv<type, double, NumberConv>(); \
add_conv<type, double const&, NumberConv>(); \
add_conv<type&, double, NumberConv>(); \
add_conv<type&, double const&, NumberConv>(); \
add_conv<type const&, double, NumberConv>(); \
add_conv<type const&, double const&, NumberConv>();

#define add_all_num_conv_impl(r, data, elem) add_num_conv(elem);
#define add_all_num_conv(SEQ) BOOST_PP_SEQ_FOR_EACH(add_all_num_conv_impl,, SEQ)

using namespace LikeMagic;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::TypeConv;
using namespace LikeMagic::Utility;

using namespace std;


DLL_PUBLIC_RUNTIME_TYPE_SYSTEM RuntimeTypeSystem* RuntimeTypeSystem::create()
{
    auto* result = new RuntimeTypeSystem();
    LikeMagic::StdBindings::add_bindings(*result);
    return result;
}


// Vector helper.  Assignment in Io cannot (?) be overloaded; it creates new
// slots rather than copying values.  This allows us to assign values to vector elements.
template <typename T>
void at_put(vector<T>& target, size_t pos, T const& value)
{
    target.at(pos) = value;
}

RuntimeTypeSystem::RuntimeTypeSystem()
{
    // The runtime type system creates the type info cache.
    // In order to get the DLLs using the same static TypeInfo instance we have to "smuggle" in a pointer to it via this object.
    dll_shared_typeinfo = new TypeInfoCache;
    TypeInfoCache::set_instance(dll_shared_typeinfo);

    Namespace global_ns = Namespace::global(*this);

    // Register proxy methods (methods that act on the ExprProxy instead of the object itself)
    // Everything below here uses proxy methods.
    static TypeIndex proxy_methods_type = BetterTypeInfo::create_index<ProxyMethodsType>();
    proxy_methods = new ProxyMethods(proxy_methods_type, "ProxyMethods", *this, NamespacePath::global());
    add_class(proxy_methods_type, proxy_methods);
    proxy_methods->bind_method("get_class", &AbstractCppObjProxy::get_class);
    proxy_methods->bind_method("get_type", &AbstractCppObjProxy::get_type);
    proxy_methods->bind_method("lm_get_type", &AbstractCppObjProxy::get_type);  // Added this because AbstractClass class_proxy also has a get_type we don't want to call
    proxy_methods->bind_method("describe", &AbstractCppObjProxy::describe);
    proxy_methods->bind_method("get_base_names", &AbstractCppObjProxy::get_base_names);

    // Allow conversions from nil to any pointer.
    static TypeIndex nil_expr_type = BetterTypeInfo::create_index<BottomPtrType>();
    conv_graph.add_type(nil_expr_type);

    // register void so functions returning void will work right.
    static TypeIndex void_type = BetterTypeInfo::create_index<void>();
    auto void_class = new DummyClass<void>(void_type, "void", *this, NamespacePath::global());
    add_class(void_type, void_class);
    void_class->add_base_abstr(proxy_methods);

    // register the Bottom Pointer so unsafe_ptr_cast will work.
    static TypeIndex bot_type = BetterTypeInfo::create_index<BottomPtrTag__>();
    auto bot_class = new DummyClass<BottomPtrTag__>(bot_type, "unsafe_ptr_cast", *this, NamespacePath::global());
    add_class(bot_type, bot_class);
    bot_class->add_base_abstr(proxy_methods);
    add_conv<BottomPtrTag__*&, BottomPtrTag__*>();
    add_conv<BottomPtrTag__* const&, BottomPtrTag__*>();

    // register the Unknown_CppObj so functions returning unregistered classes
    // can still be called.
    static TypeIndex unknown_type = BetterTypeInfo::create_index<Unknown_CppObj>();
    auto unknown_class = new DummyClass<Unknown_CppObj>(unknown_type, "Unknown_CppObj", *this, NamespacePath::global());
    add_class(unknown_type, unknown_class);
    unknown_class->add_base_abstr(proxy_methods);
    this->unknown_class = unknown_class;
}

