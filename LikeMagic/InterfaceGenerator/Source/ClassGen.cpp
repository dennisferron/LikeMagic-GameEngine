#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"

#include "LikeMagic/Mirrors/TypeMirror.hpp"

using namespace std;
using namespace LM;

ClassGen::~ClassGen() {}

void ClassGen::dump(std::ostream& os, int depth) const
{
    for (int i=0; i<depth; i++)
        os << "\t";

    write_name(os);

    os << endl;
}

TypeMirrorClassGen::TypeMirrorClassGen(TypeMirror* type_mirror_, ClassGenList const& classes_)
    : type_mirror(type_mirror_), classes(classes_)
{
    std::vector<std::pair<std::string, CallTarget*>> type_methods = type_mirror_->get_all_methods();
    for (auto kv : type_methods)
    {
        this->methods.push_back(std::move(std::unique_ptr<MethodGen>(new MethodGen(kv.first, kv.second, classes_))));
    }
}

void TypeMirrorClassGen::write_name(ostream& os) const
{
    os << get_name();
}

std::string TypeMirrorClassGen::get_name() const
{
    return type_mirror->get_class_name();
}

void TypeMirrorClassGen::write_class_name(ostream& os) const
{
    os << "struct ";
    write_name(os);
}

void TypeMirrorClassGen::declare(ostream& os) const
{
    write_class_name(os);
    os << endl << "{" << endl;
    os << "    " << "ExprPtr expr;" << endl;
    for (auto& method : methods)
    {
        os << "    ";
        os << "auto ";
        method->declare(os);
    }
    os << "};";
}

void TypeMirrorClassGen::define(ostream& os) const
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

void TypeMirrorClassGen::forward_declare(ostream& os, int depth) const
{
    for (int i=0; i<depth; i++)
        os << "\t";

    write_class_name(os);
    os << ";" << endl;
}

std::unordered_set<ClassGen const*> TypeMirrorClassGen::get_referenced_classes() const
{
    std::unordered_set<ClassGen const*> result;

    for (auto& method : methods)
    {
        auto list = method->get_referenced_classes();
        result.insert(list.begin(), list.end());
    }

    return result;
}

std::unordered_set<TypeIndex> TypeMirrorClassGen::get_referenced_types() const
{
    std::unordered_set<TypeIndex> result;

    for (auto& method : methods)
    {
        auto list = method->get_referenced_types();
        result.insert(list.begin(), list.end());
    }

    return result;
}

TypeIndex TypeMirrorClassGen::get_type() const
{
    return type_mirror->get_class_type();
}

CustomClassGen::CustomClassGen(std::string name_, TypeIndex type_, std::vector<MethodGen*> methods_, ClassGenList const& classes_)
    : name(name_), type(type_), classes(classes_)
{
    for (auto m : methods_)
    {
        this->methods.push_back(std::move(std::unique_ptr<MethodGen>(m)));
    }
}

TypeIndex CustomClassGen::get_type() const
{
    return type;
}

void CustomClassGen::write_name(ostream& os) const
{
    os << get_name();
}

std::string CustomClassGen::get_name() const
{
    static std::set<string> reserved_names = {
        "int", "double", "float", "char", "string"
    };

    if (reserved_names.find(name) != reserved_names.end())
    {
        return name + "_expr";
    }

    return name;
}

void CustomClassGen::write_class_name(ostream& os) const
{
    os << "struct ";
    write_name(os);
}

void CustomClassGen::declare(ostream& os) const
{
    write_class_name(os);
    os << endl << "{" << endl;
    os << "    " << "ExprPtr expr;" << endl;
    for (auto& method : methods)
    {
        os << "    ";
        os << "auto ";
        method->declare(os);
    }
    os << "};";
}

void CustomClassGen::define(ostream& os) const
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

void CustomClassGen::forward_declare(ostream& os, int depth) const
{
    for (int i=0; i<depth; i++)
        os << "\t";
    write_class_name(os);
    os << ";" << endl;
}

std::unordered_set<ClassGen const*> CustomClassGen::get_referenced_classes() const
{
    std::unordered_set<ClassGen const*> result;

    for (auto& method : methods)
    {
        auto list = method->get_referenced_classes();
        result.insert(list.begin(), list.end());
    }

    return result;
}

std::unordered_set<TypeIndex> CustomClassGen::get_referenced_types() const
{
    std::unordered_set<TypeIndex> result;

    for (auto& method : methods)
    {
        auto list = method->get_referenced_types();
        result.insert(list.begin(), list.end());
    }

    return result;
}

