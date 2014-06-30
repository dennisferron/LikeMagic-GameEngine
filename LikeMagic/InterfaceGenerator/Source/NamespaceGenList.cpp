#include "InterfaceGenerator/NamespaceGenList.hpp"
#include "InterfaceGenerator/NamespaceGen.hpp"
#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"
#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"

using namespace LM;

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

void NamespaceGenList::add_class(TypeIndex index, ClassGen const* class_gen)
{
    auto result = namespaces.find(index);
    if (result == namespaces.end())
    {
        throw std::logic_error("Different NamespaceGen already registered for type " + index.description());
    }
    else
    {
        namespaces[index]->add_class(class_gen);
    }
}

bool NamespaceGenList::has_namespace(TypeIndex index) const
{
    auto result = namespaces.find(index);
    return result != namespaces.end();
}
