
#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/NamespaceGen.hpp"

#include "LikeMagic/Mirrors/TypeMirror.hpp"

#include <algorithm>

using namespace std;
using namespace LM;

NamespaceGen::~NamespaceGen() {}

void NamespaceGen::dump(std::ostream& os, int depth) const
{
    for (int i=0; i<depth; i++)
        os << "\t";

    write_namespace_name(os);
    os << endl;

    for (auto class_ : get_child_classes())
    {
        class_->dump(os, depth+1);
    }

    for (auto child_ns : get_child_namespaces())
    {
        child_ns->dump(os, depth+1);
    }
}

std::vector<NamespaceGen const*> NamespaceGen::get_full_namespace() const
{
    std::vector<NamespaceGen const*> result;

    if (!is_root())
        result = get_parent_namespace()->get_full_namespace();

    result.push_back(this);

    return result;
}

std::string NamespaceGen::get_file_name() const
{
    if (this->is_root())
    {
        return "ns_global";
    }
    else
    {
        std::string result;
        for (auto ns : get_full_namespace())
        {
            if (ns->is_root())
                result = "ns";
            else
                result += "_" + ns->get_name();
        }
        return result;
    }
}

bool NamespaceGen::is_root() const
{
    return get_parent_namespace() == nullptr || get_parent_namespace() == this;
}

TypeMirrorNamespaceGen::~TypeMirrorNamespaceGen() {}

TypeMirrorNamespaceGen::TypeMirrorNamespaceGen(TypeMirror* type_mirror_, ClassGenList const& classes_)
    : type_mirror(type_mirror_), classes(classes_), parent(nullptr)
{
}

NamespaceGen* TypeMirrorNamespaceGen::get_parent_namespace() const
{
    return parent;
}

void TypeMirrorNamespaceGen::set_parent_namespace(NamespaceGen* ns_gen)
{
    parent = ns_gen;
}

void TypeMirrorNamespaceGen::add_child(NamespaceGen* child_ns)
{
    children.insert(child_ns);
    child_ns->set_parent_namespace(this);
}

void TypeMirrorNamespaceGen::add_class(ClassGen* class_)
{
    child_classes.insert(class_);
    class_->set_namespace(this);
}

void TypeMirrorNamespaceGen::write_name(ostream& os) const
{
    os << get_name();
}

std::string TypeMirrorNamespaceGen::get_name() const
{
    if (type_mirror->get_class_name() == "")
        return "GameBindings";
    else
        return type_mirror->get_class_name();
}

void TypeMirrorNamespaceGen::write_namespace_name(ostream& os) const
{
    os << "namespace ";
    write_name(os);
}

void TypeMirrorNamespaceGen::open(ostream& os, int depth) const
{
    for (int i=0; i<depth; i++)
        os << "\t";
    write_namespace_name(os);
    os << endl;
    for (int i=0; i<depth; i++)
        os << "\t";
    os << "{" << endl;
}

void TypeMirrorNamespaceGen::close(ostream& os, int depth) const
{
    for (int i=0; i<depth; i++)
        os << "\t";
    os << "}" << endl;
}

void TypeMirrorNamespaceGen::using_(ostream& os) const
{
    os << "using ";
    write_namespace_name(os);
    os << ";" << endl;
}

bool TypeMirrorNamespaceGen::has_descendant_class(std::set<ClassGen*> class_gens) const
{
    for (auto c : child_classes)
    {
        if (class_gens.find(c) != class_gens.end())
        {
            return true;
        }
    }

    for (auto ns : children)
    {
        if (ns->has_descendant_class(class_gens))
            return true;
    }

    return false;
}

std::set<ClassGen*> TypeMirrorNamespaceGen::get_child_classes() const
{
    return child_classes;
}

std::set<NamespaceGen*> TypeMirrorNamespaceGen::get_child_namespaces() const
{
    return children;
}

TypeIndex TypeMirrorNamespaceGen::get_type() const
{
    return type_mirror->get_class_type();
}
