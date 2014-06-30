
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <ostream>

namespace LM {

class ClassGen;
class ClassGenList;

class RetGen
{
private:
    TypeIndex ret_type;
    ClassGenList const& classes;

public:
    RetGen(TypeIndex ret_type_, ClassGenList const& classes_);
    virtual ~RetGen();
    void declare(std::ostream& os) const;
    void define(std::ostream& os) const;
    ClassGen const* get_class() const;
    TypeIndex get_type() const;
};

}
