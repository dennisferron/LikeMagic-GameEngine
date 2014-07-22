
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
    NamespaceGen* root;

public:
    ~NamespaceGenList();
    NamespaceGen const* get_namespace(TypeIndex ns_type) const;
    void add_namespace(TypeIndex index, NamespaceGen* namespace_gen);
    void add_class(TypeIndex parent_namespace_type, ClassGen* class_gen);
    void add_child_namespace(TypeIndex parent_namespace_type, NamespaceGen* namespace_gen);
    bool has_namespace(TypeIndex ns_type) const;
    std::set<NamespaceGen*> get_all_namespaces() const;
    void set_root(NamespaceGen* root_);
};

}


