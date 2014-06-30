
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <ostream>

namespace LM {

class ClassGen;
class ClassGenList;

class ArgGen
{
private:
    TypeInfoList args;
    int pos;
    ClassGenList const& classes;

    TypeIndex get_arg_type() const;
    void write_arg_type(std::ostream& os) const;
    void write_arg_name(std::ostream& os) const;

public:
    ArgGen(TypeInfoList args_, int pos_, ClassGenList const& classes_);
    virtual ~ArgGen();
    void declare(std::ostream& os) const;
    void define(std::ostream& os) const;
    void invoke(std::ostream& os) const;
    ClassGen const* get_class() const;
    TypeIndex get_type() const;
};

}
