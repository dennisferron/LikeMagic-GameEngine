#define LM_BINDING_FUNCTIONS_CPP
#include "LikeMagic/binding_functions.hpp"

#include "boost/preprocessor/punctuation/comma_if.hpp"
#include "boost/preprocessor/control/if.hpp"

using namespace LM;
using namespace std;

namespace LM {

std::string create_constructor_name(std::string prefix, std::string method_name)
{
    if (method_name.substr(0, 3) == "new")
        return prefix + method_name.substr(3);
    else
        return prefix + "_" + method_name;
}

LM::TypeMirror& register_namespace(std::string name, TypeMirror& parent_namespace_)
{
    std::string full_name = parent_namespace_.get_class_name() + "::" + name;
    const TypeIndex namespace_type(LM::create_namespace_type_index(full_name));
    std::cout << "Registering namespace " << full_name << " as type " << namespace_type.description() << endl;

    if (type_system->get_class(namespace_type))
    {
        return *(type_system->get_class(namespace_type));
    }
    else
    {
        auto result = create_type_mirror(name, size_t(0), namespace_type);
        type_system->add_class(namespace_type, result, parent_namespace_);
        return *result;
    }
}

}
