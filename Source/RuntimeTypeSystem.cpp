
#include "LikeMagic/RuntimeTypeSystem.hpp"

#include "LikeMagic/TypeConv/StringConv.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::TypeConv;

RuntimeTypeSystem::RuntimeTypeSystem()  :
    functions("CppFunc", *this),
    proxy_methods("ProxyMethods", *this),
    collection_methods("CollectionMethods", *this)
{
    // Add the abstract type system itself as a class.
    LM_CLASS_NO_COPY((*this), AbstractTypeSystem)
    LM_FUNC(AbstractTypeSystem, (set_leak_memory)(leak_memory))

    // Register the special classes
    classes[BetterTypeInfo::create<StaticMethod>()] = &functions;
    classes[BetterTypeInfo::create<AbstractCppObjProxy>()] = &proxy_methods;
    classes[BetterTypeInfo::create<SFMOCollection>()] = &collection_methods;

    // StaticMethods is by value but a Term returns by reference;
    // need to give type system ability to do the conversion.
    add_conv<StaticMethod&, StaticMethod>();

    collection_methods.bind_method("each", &AbstractCppObjProxy::each);

    proxy_methods.bind_method("eval", &AbstractCppObjProxy::eval);
    proxy_methods.bind_method("exec", &AbstractCppObjProxy::exec);
    proxy_methods.bind_method("lazy", &AbstractCppObjProxy::lazy);

    proxy_methods.bind_method("elem", &AbstractCppObjProxy::elem);
    proxy_methods.bind_method("iterate", &AbstractCppObjProxy::iterate);
    proxy_methods.bind_method("adv_loop", &AbstractCppObjProxy::adv_loop);
    proxy_methods.bind_method("begin_loop", &AbstractCppObjProxy::begin_loop);
    proxy_methods.bind_method("loop_at_end", &AbstractCppObjProxy::loop_at_end);

    proxy_methods.bind_method("describe", &AbstractCppObjProxy::describe);

    // register void so functions returning void will work right.
    auto void_class = new DummyClass<void>("void", *this);
    classes[BetterTypeInfo::create<void>()] = void_class;
    void_class->add_base_abstr(&proxy_methods);

    // register the Unknown_CppObj so functions returning unregistered classes
    // can still be called.
    auto unknown_class = new DummyClass<Unknown_CppObj>("Unknown_CppObj", *this);
    classes[BetterTypeInfo::create<Unknown_CppObj>()] = unknown_class;
    unknown_class->add_base_abstr(&proxy_methods);
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
    register_class<bool>("bool");


    // When IoNil is encountered, it is marshaled as a NullExpr<void*> object,
    // which is an expression   of type of void* that always returns NULL.
    // Some fancy magic happens in try_conv to intercept the void* NULL value
    // and replace it with a NullExpr of the appropriate pointer type for the function argument.
    register_class<void*>("void_ptr");

    add_conv<  double&,         unsigned short,   NumberConv>();
    add_conv<  double&,         unsigned short&,   NumberConv>();
    add_conv<  double&,         unsigned int,   NumberConv>();
    add_conv<  double&,         unsigned int&,   NumberConv>();
    add_conv<  double&,         unsigned long,   NumberConv>();
    add_conv<  double&,         unsigned long&,   NumberConv>();

    add_conv<  double&,         short,   NumberConv>();
    add_conv<  double&,         short&,   NumberConv>();
    add_conv<  double&,         int,   NumberConv>();
    add_conv<  double&,         int&,   NumberConv>();
    add_conv<  double&,         long,   NumberConv>();
    add_conv<  double&,         long&,   NumberConv>();


    add_conv<  double&,         float,   NumberConv>();
    add_conv<  double&,         float&,   NumberConv>();

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

    // enable std::vector conversions to pointers for primitives
    //register_collection<unsigned short>("ushort");
}

