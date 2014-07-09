#include "InterfaceGenerator/NamespaceGenList.hpp"
#include "InterfaceGenerator/NamespaceGen.hpp"
#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"

using namespace LM;

void NamespaceGenList::set_root(NamespaceGen* root_)
{
    root = root_;
}

NamespaceGenList::~NamespaceGenList()
{
    for (auto i : namespaces)
    {
        delete i.second;
    }
}

NamespaceGen const* NamespaceGenList::get_namespace(TypeIndex index) const
{
    auto result = namespaces.find(index);
    if (result == namespaces.end())
    {
        std::cerr << "No NamespaceGen for type " + index.description() << " " << index.get_id() << std::endl;
        throw std::logic_error("No NamespaceGen for type " + index.description());
    }
    return result->second;
}

void NamespaceGenList::add_namespace(TypeIndex index, NamespaceGen* namespace_gen)
{
    auto result = namespaces.find(index);
    if (result != namespaces.end() && result->second != namespace_gen)
    {
        throw std::logic_error("Different NamespaceGen already registered for type " + index.description());
    }
    else
    {
        namespaces[index] = namespace_gen;
    }
}

void NamespaceGenList::add_class(TypeIndex parent_namespace_type, ClassGen const* class_gen)
{
    auto result = namespaces.find(parent_namespace_type);
    if (result == namespaces.end())
    {
        throw std::logic_error("No NamespaceGen found for type " + parent_namespace_type.description());
    }
    else
    {
        namespaces[parent_namespace_type]->add_class(class_gen);
    }
}

void NamespaceGenList::add_child_namespace(TypeIndex parent_namespace_type, NamespaceGen* namespace_gen)
{
    if (namespace_gen == root)
        throw std::logic_error("Cannot add root namespace as a child namespace.");

    auto result = namespaces.find(parent_namespace_type);
    if (result == namespaces.end())
    {
        throw std::logic_error("No NamespaceGen found for type " + parent_namespace_type.description());
    }
    else
    {
        namespaces[parent_namespace_type]->add_child(namespace_gen);
    }
}

bool NamespaceGenList::has_namespace(TypeIndex index) const
{
    auto result = namespaces.find(index);
    return result != namespaces.end();
}

std::set<NamespaceGen*> NamespaceGenList::get_all_namespaces() const
{
    std::set<NamespaceGen*> result;
    for (auto i : namespaces)
    {
        result.insert(i.second);
    }
    return result;
}
