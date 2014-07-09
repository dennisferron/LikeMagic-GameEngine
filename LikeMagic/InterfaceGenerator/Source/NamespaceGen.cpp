
#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/NamespaceGen.hpp"

#include "LikeMagic/Mirrors/TypeMirror.hpp"

using namespace std;
using namespace LM;

NamespaceGen::~NamespaceGen() {}

TypeMirrorNamespaceGen::~TypeMirrorNamespaceGen() {}

TypeMirrorNamespaceGen::TypeMirrorNamespaceGen(TypeMirror* type_mirror_, ClassGenList const& classes_)
    : type_mirror(type_mirror_), classes(classes_)
{
}

void TypeMirrorNamespaceGen::add_child(NamespaceGen* child_ns)
{
    children.push_back(child_ns);
}

void TypeMirrorNamespaceGen::add_class(ClassGen const* class_)
{
    child_classes.insert(class_);
}

void TypeMirrorNamespaceGen::write_name(ostream& os) const
{
    os << get_name();
}

std::string TypeMirrorNamespaceGen::get_name() const
{
    return type_mirror->get_class_name();
}

void TypeMirrorNamespaceGen::write_namespace_name(ostream& os) const
{
    os << "namespace ";
    write_name(os);
}

void TypeMirrorNamespaceGen::open(ostream& os) const
{
    write_namespace_name(os);
    os << endl << "{" << endl;
}

void TypeMirrorNamespaceGen::close(ostream& os) const
{
    os << "}" << endl;
}

void TypeMirrorNamespaceGen::using_(ostream& os) const
{
    os << "using ";
    write_namespace_name(os);
    os << ";" << endl;
}

void TypeMirrorNamespaceGen::has_descendant_class(ClassGen const* class_gen)
{
    throw std::logic_error("Not implemented");
}

std::set<ClassGen const*> TypeMirrorNamespaceGen::get_child_classes() const
{
    throw std::logic_error("Not implemented");
}

TypeIndex TypeMirrorNamespaceGen::get_type() const
{
    return type_mirror->get_class_type();
}

/* TODO:
    Move this to Generator

void TypeMirrorNamespaceGen::forward_declare(ostream& os, std::set<ClassGen const*> classes_) const
{
    std::set<ClassGen const*> descendants_intersect = get_descendants(classes_);

    if (descendants_intersect.size() > 0)
    {
        open(os);

        for (auto child : children)
        {
            child->forward_declare(os, intersect);
        }

        std::set<ClassGen const*> child_intersect;
        set_intersection(
            child_classes.begin(), child_classes.end(),
            descendants_intersect.begin(), descendants_intersect.end(),
            std::inserter(child_intersect, child_intersect.begin()));

        for (auto direct_child : child_intersect)
        {
            direct_child->forward_declare(os);
        }

        close(os);
    }
}

std::set<ClassGen const*> TypeMirrorNamespaceGen::get_referenced_classes() const
{
    throw std::logic_error("Not implemented");
}

std::set<TypeIndex> TypeMirrorNamespaceGen::get_referenced_types() const
{
    throw std::logic_error("Not implemented");
}

std::set<NamespaceGen const*> TypeMirrorNamespaceGen::get_referenced_namespaces() const
{
    throw std::logic_error("Not implemented");
}

*/
