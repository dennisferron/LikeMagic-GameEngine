
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace LM {

class TypeMirror;
class MethodGen;

class ClassGen
{
private:
    TypeMirror* type_mirror;
    std::unordered_map<TypeIndex, ClassGen const*> const& classes;
    std::vector<std::unique_ptr<MethodGen>> methods;

    std::unordered_set<ClassGen const*> referenced_classes() const;

public:
    ClassGen(TypeMirror* type_mirror_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_);
    void declare(std::ostream& os) const;
    void define(std::ostream& os) const;
    void forward_declare(std::ostream& os) const;
    void write_name(std::ostream& os) const;
    void write_class_name(std::ostream& os) const;
};

}
