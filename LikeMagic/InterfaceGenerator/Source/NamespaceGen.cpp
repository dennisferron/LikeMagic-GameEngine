
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

void TypeMirrorNamespaceGen::declare(ostream& os) const
{
    write_namespace_name(os);
    os << endl << "{" << endl;
    os << "}" << endl;
}

void TypeMirrorNamespaceGen::define(ostream& os, std::set<ClassGen const*> classes_) const
{
    std::set<ClassGen const*> intersect = get_descendants(classes_);

    if (intersect.size() > 0)
    {
        open(os);

        for (auto child : children)
        {
            child->define(os, intersect);
        }

        for (auto class_ : intersect)
        {
            if (child_classes.find(class_) != child_classes.end())
            {
                class_->define(os);
            }
        }

        close(os);
    }
}

/* TODO:
    1. Create HierarchyGen interface/base class
    2. Create HierarchyVisitor which contains the algorithm below
    3. Take the operation to do (forward declare, declare, or define) as a functoid.
*/

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

std::unordered_set<ClassGen const*> TypeMirrorNamespaceGen::get_referenced_classes() const
{
    throw std::logic_error("Not implemented");
}

std::unordered_set<TypeIndex> TypeMirrorNamespaceGen::get_referenced_types() const
{
    throw std::logic_error("Not implemented");
}

std::unordered_set<NamespaceGen const*> TypeMirrorNamespaceGen::get_referenced_namespaces() const
{
    throw std::logic_error("Not implemented");
}

