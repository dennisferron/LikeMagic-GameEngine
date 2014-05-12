
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <ostream>
#include <unordered_map>

namespace LM {

class ClassGen;

class RetGen
{
private:
    TypeIndex ret_type;
    std::unordered_map<TypeIndex, ClassGen const*> const& classes;

public:
    RetGen(TypeIndex ret_type_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_);
    void declare(std::ostream& os) const;
    void define(std::ostream& os) const;
    ClassGen const* get_class() const;
};

}
