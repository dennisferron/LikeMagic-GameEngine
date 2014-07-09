
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <unordered_map>

namespace LM {

class ClassGen;

class ClassGenList
{
private:
    std::unordered_map<TypeIndex, ClassGen const*> classes;

    TypeIndex get_class_type(TypeIndex index) const;

public:
    ~ClassGenList();
    ClassGen const* get_class(TypeIndex index) const;
    void add_class(TypeIndex index, ClassGen const* class_gen);
    bool has_class(TypeIndex index) const;
    std::set<ClassGen const*> get_all_classes() const;
};

}

