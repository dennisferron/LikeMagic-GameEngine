// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "LikeMagic/NamespacePath.hpp"

#include "LikeMagic/TypeConv/StringConv.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"

#include "boost/preprocessor/seq/for_each.hpp"

#define add_num_conv(type) \
add_conv<type, type const&, NumberConv>(); \
add_conv<type&, type, NumberConv>(); \
add_conv<type const&, type, NumberConv>(); \
add_conv<double, type, NumberConv>(); \
add_conv<double, type const&, NumberConv>(); \
add_conv<double&, type, NumberConv>(); \
add_conv<double&, type const&, NumberConv>(); \
add_conv<double const&, type, NumberConv>(); \
add_conv<double const&, type const&, NumberConv>(); \
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


RuntimeTypeSystem::RuntimeTypeSystem()
{
    // The runtime type system creates the type info cache.
    // In order to get the DLLs using the same static TypeInfo instance we have to "smuggle" in a pointer to it via this object.
    dll_shared_typeinfo = new TypeInfoCache;
    TypeInfoCache::set_instance(dll_shared_typeinfo);

    // Register the special classes
    static TypeIndex proxy_methods_type = BetterTypeInfo::create_index<ProxyMethodsType>();
    //static TypeIndex collection_methods_type = BetterTypeInfo::create_index<SFMOCollection>();

    //functions = new StaticMethods(*this, NamespacePath::global());
    proxy_methods = new ProxyMethods(proxy_methods_type, "ProxyMethods", *this, NamespacePath::global());
    //collection_methods = new ProxyMethods(collection_methods_type, "CollectionMethods", *this, NamespacePath::global());


    // Allow conversions from nil to any pointer.
    static TypeIndex nil_expr_type = BetterTypeInfo::create_index<NilExprTag*>();
    conv_graph.add_type(nil_expr_type);

    // Add the abstract type system itself as a class.
    LM_CLASS_NO_COPY((*this), AbstractTypeSystem)
    LM_FUNC(AbstractTypeSystem, (set_leak_memory)(leak_memory)(add_type_system_observer))

    LM_CLASS_NO_COPY((*this), AbstractCppObjProxy)

    LM_CLASS_NO_COPY((*this), AbstractClass)
    LM_FUNC(AbstractClass, (get_class_name)(get_type)(create_class_proxy)(get_namespace)(get_method_names))

    LM_CLASS((*this), TypeIndex)
    LM_FUNC(TypeIndex, (describe))

    LM_CLASS_NO_COPY((*this), NamespacePath)
    LM_FUNC(NamespacePath, (is_root)(get_name)(get_parent)(to_string))

    //add_class(functions->get_type(), functions);
    add_class(proxy_methods_type, proxy_methods);
    //add_class(collection_methods_type, collection_methods);

    // If you think you need this binding, more likely you're doing something else wrong:
    // (StaticMethods' type info is supposed to be a NamespaceTypeInfo, not a reference to StaticMethods).
    //LM_CLASS_NO_COPY((*this), StaticMethods)

    // StaticMethods is by value but a Term returns by reference;
    // need to give type system ability to do the conversion.
    //add_conv<StaticMethod&, StaticMethod>();
    //add_conv<StaticMethod const&, StaticMethod>();

    //collection_methods->bind_method("each", &AbstractCppObjProxy::each);

    proxy_methods->bind_method("eval", &AbstractCppObjProxy::eval);
    proxy_methods->bind_method("exec", &AbstractCppObjProxy::exec);
    proxy_methods->bind_method("lazy", &AbstractCppObjProxy::lazy);
    proxy_methods->bind_method("get_class", &AbstractCppObjProxy::get_class);
    proxy_methods->bind_method("get_type", &AbstractCppObjProxy::get_type);
    proxy_methods->bind_method("lm_get_type", &AbstractCppObjProxy::get_type);  // Added this because AbstractClass class_proxy also has a get_type we don't want to call
    proxy_methods->bind_method("describe", &AbstractCppObjProxy::describe);
    proxy_methods->bind_method("get_base_names", &AbstractCppObjProxy::get_base_names);

    // register void so functions returning void will work right.
    static TypeIndex void_type = BetterTypeInfo::create_index<void>();
    auto void_class = new DummyClass<void>(void_type, "void", *this, NamespacePath::global());
    add_class(void_type, void_class);
    void_class->add_base_abstr(proxy_methods);

    // register the Unknown_CppObj so functions returning unregistered classes
    // can still be called.
    static TypeIndex unknown_type = BetterTypeInfo::create_index<Unknown_CppObj>();
    auto unknown_class = new DummyClass<Unknown_CppObj>(unknown_type, "Unknown_CppObj", *this, NamespacePath::global());
    add_class(unknown_type, unknown_class);
    unknown_class->add_base_abstr(proxy_methods);
    this->unknown_class = unknown_class;

    register_class<std::string>("string");
    register_class<std::wstring>("wstring");
    register_class<short>("short");
    register_class<unsigned short>("ushort");
    register_class<int>("int");
    register_class<unsigned int>("uint");
    register_class<long>("long");
    register_class<unsigned long>("ulong");
    register_class<double>("double");
    register_class<float>("float");
    register_class<bool>("bool");


    // When IoNil is encountered, it is marshaled as a NullExpr<void*> object,
    // which is an expression   of type of void* that always returns NULL.
    // Some fancy magic happens in try_conv to intercept the void* NULL value
    // and replace it with a NullExpr of the appropriate pointer type for the function argument.
    add_conv<void*&, void*>();

    add_all_num_conv((signed char)(short)(int)(long)(unsigned char)(unsigned short)(unsigned int)(unsigned long)(float)(double))

    // Allow string conversions
    add_conv<  std::string&,    std::wstring,   StringConv>();
    add_conv<  std::string&,    wchar_t const*, StringConv>();
    add_conv<  std::string&,    char const*,    StringConv>();

    add_conv<  std::wstring,    std::string,    StringConv>();
    add_conv<  std::wstring&,   std::string,    StringConv>();
    add_conv<  wchar_t const*,  std::string,    StringConv>();
    add_conv<  wchar_t const*&, std::string,    StringConv>();
    add_conv<  char const*,     std::string,    StringConv>();
    add_conv<  char const*&,    std::string,    StringConv>();

    // Allow char*& terms to be converted to char* values.
    add_conv<  char const*&,    char const*,    ImplicitConv>();

    // enable std::vector conversions to pointers for primitives
    //register_collection<unsigned short>("ushort");
    register_class<std::vector<int>>("vector_of_int");
    register_class<std::vector<unsigned int>>("vector_of_uint");
    register_class<std::vector<short>>("vector_of_short");
    register_class<std::vector<unsigned short>>("vector_of_ushort");

    typedef vector<string> vector_of_string;
    LM_CLASS((*this), vector_of_string)
    LM_FUNC(vector_of_string, (size))
    LM_FUNC_OVERLOAD_BOTH(vector_of_string, at, string&, vector_of_string::size_type)
    //LM_FUNC_OVERLOAD(vector_of_string, "at", at, vector_of_string::reference, size_type)
    //LM_FUNC_OVERLOAD_CONST(vector_of_string, "at", at, vector_of_string::const_reference, vector_of_string::size_type)
}


StaticMethods& RuntimeTypeSystem::register_functions(NamespacePath const ns)
{
    TypeIndex type = ns.get_type();
    //cout << "Register functions type index = " << type.get_id() << " " << type.describe() << endl;

    if (has_class(type))
        return cast_existing_class<StaticMethods>(type, true);
    else
    {
        StaticMethods* result = new StaticMethods(*this, ns);
        add_class(result->get_type(), result);
        result->add_base_abstr(proxy_methods);
        return *result;
    }
}

