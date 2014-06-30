
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <unordered_map>

namespace LM {

class NamespaceGen;
class ClassGen;

class NamespaceGenList
{
private:
    std::unordered_map<TypeIndex, NamespaceGen*> namespaces;

public:
    ~NamespaceGenList();
    NamespaceGen const* get_namespace(TypeIndex ns_type) const;
    void add_namespace(TypeIndex index, NamespaceGen* namespace_gen);
    void add_class(TypeIndex ns_type, ClassGen const* class_gen);
    bool has_namespace(TypeIndex ns_type) const;
};

}


