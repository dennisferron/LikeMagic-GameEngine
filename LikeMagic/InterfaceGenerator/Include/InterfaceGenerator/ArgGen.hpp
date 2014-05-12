
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <ostream>
#include <unordered_map>

namespace LM {

class ClassGen;

class ArgGen
{
private:
    TypeInfoList args;
    int pos;
    std::unordered_map<TypeIndex, ClassGen const*> const& classes;

    TypeIndex get_arg_type() const;
    void write_arg_type(std::ostream& os) const;
    void write_arg_name(std::ostream& os) const;

public:
    ArgGen(TypeInfoList args_, int pos_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_);
    void declare(std::ostream& os) const;
    void invoke(std::ostream& os) const;
    ClassGen const* get_class() const;
};

}
