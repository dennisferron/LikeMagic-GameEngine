
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <unordered_set>

namespace LM {

class CallTarget;
class ArgGen;
class RetGen;
class ClassGen;
class ClassGenList;

class MethodGen
{
private:
    std::string name;
    CallTarget* call_target;
    std::unique_ptr<RetGen> ret;
    std::vector<std::unique_ptr<ArgGen>> args;
    ClassGenList const& classes;

public:
    MethodGen(std::string name_, CallTarget* call_target_, ClassGenList const& classes_);
    virtual ~MethodGen();
    void declare(std::ostream& os) const;
    void define(std::ostream& os) const;
    std::unordered_set<TypeIndex> get_referenced_types() const;
    std::unordered_set<ClassGen*> get_referenced_classes() const;
    std::string get_name() const;
};

}
