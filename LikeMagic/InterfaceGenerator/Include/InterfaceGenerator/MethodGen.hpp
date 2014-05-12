
#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"

#include <string>
#include <vector>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <unordered_set>

namespace LM {

class CallTarget;
class ArgGen;
class RetGen;
class ClassGen;

class MethodGen
{
private:
    std::string name;
    CallTarget* call_target;
    std::unique_ptr<RetGen> ret;
    std::vector<std::unique_ptr<ArgGen>> args;
    std::unordered_map<TypeIndex, ClassGen const*> const& classes;

public:
    MethodGen(std::string name_, CallTarget* call_target_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_);
    void declare(std::ostream& os) const;
    void define(std::ostream& os) const;
    std::unordered_set<ClassGen const*> get_referenced_types() const;
};

}
