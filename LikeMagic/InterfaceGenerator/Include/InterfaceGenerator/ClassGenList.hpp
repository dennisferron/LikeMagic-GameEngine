
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <unordered_map>

namespace LM {

class ClassGen;

class ClassGenList
{
private:
    std::unordered_map<TypeIndex, ClassGen*> classes;

    TypeIndex get_class_type(TypeIndex index) const;

public:
    ~ClassGenList();
    ClassGen* get_class(TypeIndex index) const;
    void add_class(TypeIndex index, ClassGen* class_gen);
    bool has_class(TypeIndex index) const;
    std::set<ClassGen*> get_all_classes() const;
};

}

