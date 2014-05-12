#include "InterfaceGenerator/Generator.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Mirrors/TypeMirror.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"

#include "LIkeMagic/Utility/TypeIndex.hpp"

#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"

#include <ostream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

namespace LM {
class Generator
{
private:
    void print_class(TypeMirror& type, ostream& os);
    void print_method(std::string name, CallTarget& method, ostream& os);
    std::string generate_return_type(TypeIndex type);
    std::string generate_arg_type(TypeIndex type);
    std::string generate_arg_name(TypeInfoList types, int index);
public:
    void generate_all(std::ostream& os);
};

LIKEMAGIC_API void generate_interface_classes()
{
    Generator g;
    g.generate_all(cout);
}

}

using namespace LM;

std::string Generator::generate_return_type(TypeIndex type)
{
    return "std::shared_ptr<" + type.get_info().name + ">";
}

std::string Generator::generate_arg_type(TypeIndex type)
{
    return type.get_info().name;
}

std::string Generator::generate_arg_name(TypeInfoList types, int index)
{
    stringstream ss;
    ss << "arg";
    ss << index;
    return ss.str();
}

void Generator::print_class(TypeMirror& type, ostream& os)
{
    string name = type.get_class_name();
    os << name << endl;

    std::vector<std::pair<std::string, CallTarget*>> methods = type.get_all_methods();
    for (auto kv : methods)
    {
        print_method(kv.first, *kv.second, os);
    }
}

void Generator::print_method(std::string name, CallTarget& method, ostream& os)
{
    os << "    auto ";
    os << name;
    os << "(";

    TypeInfoList arg_types = method.get_arg_types();
    for (size_t i = 0; i < arg_types.size(); ++i)
    {
        if (i > 0)
            os << ", ";

        os << generate_arg_type(arg_types[i]);
        os << " ";
        os << generate_arg_name(arg_types, i);
    }

    os << ") -> ";
    TypeIndex rtype = method.get_return_type();
    os << generate_return_type(rtype);
    //os << ";" << endl;
    os << endl;
    os << "    "  << "{" << endl;

    os << "    " << "    ";

    if (rtype.get_id() != TypId<void>::liberal().get_id())
        os << "return call_retv";
    else
        os << "call_void";

    os << "(\"" << name << "\"";
    if (arg_types.size() > 0)
    {
        os << ", ";
        os << "{";
        for (size_t i = 0; i < arg_types.size(); ++i)
        {
            if (i > 0)
                os << ", ";
            os << generate_arg_name(arg_types, i);
        }
        os << endl;
        os << "}";
    }
    os << ");" << endl;

    os << "    " << "}" << endl;
}

void Generator::generate_all(ostream& os)
{
    if (type_system == nullptr)
        throw std::logic_error("type_system pointer not set");

    std::unordered_map<TypeIndex, ClassGen const*> classes;

    for (auto t : type_system->list_class_types())
    {
        TypeMirror* type = type_system->get_class(t);
        classes[t] = new ClassGen(type, classes);
    }

    for (auto t : type_system->list_class_types())
    {
        classes[t]->forward_declare(os);
        classes[t]->declare(os);
        classes[t]->define(os);
    }

    for (auto t : type_system->list_class_types())
    {
        delete classes[t];
    }
}
