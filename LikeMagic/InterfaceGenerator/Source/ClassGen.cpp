#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"

#include "LikeMagic/Mirrors/TypeMirror.hpp"

using namespace std;
using namespace LM;

ClassGen::ClassGen(TypeMirror* type_mirror_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_)
    : type_mirror(type_mirror_), classes(classes_)
{
    std::vector<std::pair<std::string, CallTarget*>> type_methods = type_mirror_->get_all_methods();
    for (auto kv : type_methods)
    {
        this->methods.push_back(std::move(std::unique_ptr<MethodGen>(new MethodGen(kv.first, kv.second, classes_))));
    }
}

void ClassGen::write_name(ostream& os) const
{
    string name = type_mirror->get_class_name();
    os << name << endl;
}

void ClassGen::write_class_name(ostream& os) const
{
    os << "class ";
    write_name(os);
}

void ClassGen::declare(ostream& os) const
{
    write_class_name(os);
    os << endl << "{" << endl;
    for (auto& method : methods)
    {
        method->declare(os);
        os << endl;
    }
    os << "};";
}

void ClassGen::define(ostream& os) const
{
    for (auto& method : methods)
    {
        os << "auto ";
        write_name(os);
        os << "::";
        method->define(os);
    }

    os << endl;
}

void ClassGen::forward_declare(ostream& os) const
{
    write_class_name(os);
    os << ";" << endl;
}
