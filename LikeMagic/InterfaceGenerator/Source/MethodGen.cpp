#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"

#include "LikeMagic/Mirrors/CallTarget.hpp"

using namespace LM;
using namespace std;

MethodGen::MethodGen(std::string name_, CallTarget* call_target_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_)
    : name(name_), call_target(call_target_), classes(classes_)
{
    TypeIndex rtype = call_target_->get_return_type();
    ret = std::unique_ptr<RetGen>(new RetGen(rtype, classes_));

    TypeInfoList arg_types = call_target_->get_arg_types();
    for (size_t i = 0; i < arg_types.size(); ++i)
    {
        args.push_back(std::move(std::unique_ptr<ArgGen>(new ArgGen(arg_types, i, classes_))));
    }
}

void MethodGen::declare(std::ostream& os) const
{
    os << name;
    os << "(";
    for (auto& arg : args)
        arg->declare(os);
    os << ") -> ";
    ret->declare(os);
    os << ";" << endl;
}

void MethodGen::define(std::ostream& os) const
{
    os << name;
    os << "(";
    for (auto& arg : args)
        arg->define(os);
    os << ") -> ";
    ret->define(os);
    os << "{" << endl;
    os << "}" << endl;
}

std::unordered_set<ClassGen const*> MethodGen::get_referenced_types() const
{
    std::unordered_set<ClassGen const*> result;

    for (auto& arg : args)
        result.insert(arg->get_class());

    result.insert(ret->get_class());
    return result;
}
