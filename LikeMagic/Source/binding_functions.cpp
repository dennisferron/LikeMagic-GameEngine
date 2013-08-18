#include "LikeMagic/binding_functions.hpp"

using namespace LikeMagic;

namespace LikeMagic {

std::string create_constructor_name(std::string prefix, std::string method_name)
{
    if (method_name.substr(0, 3) == "new")
        return prefix + method_name.substr(3);
    else
        return prefix + "_" + method_name;
}

LikeMagic::Mirrors::TypeMirror& register_namespace(std::string name, TypeMirror& parent_namespace_)
{
    static const TypeIndex namespace_type(LikeMagic::Utility::NamespaceTypeInfo::create_index(name));

    parent_namespace_.add_method
    (
        name, new LikeMagic::CallTargets::ExprTarget
        (
            LikeMagic::Exprs::NamespaceExpr::create
            (
                namespace_type, namespace_type
            )
        )
    );

    if (type_system->get_class(namespace_type))
    {
        return *(type_system->get_class(namespace_type));
    }
    else
    {
        auto result = new LikeMagic::Mirrors::TypeMirror(name, 0,
                            namespace_type, namespace_type, namespace_type);
        type_system->add_class(namespace_type, result);
        return *result;
    }
}

}
