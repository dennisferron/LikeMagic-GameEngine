#include "InterfaceGenerator/MethodGen.hpp"
#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"

#include "LikeMagic/Mirrors/CallTarget.hpp"

using namespace LM;
using namespace std;

MethodGen::~MethodGen() {}

MethodGen::MethodGen(std::string name_, CallTarget* call_target_, ClassGenList const& classes_)
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

std::string MethodGen::get_name() const
{
    static std::set<string> operators = {
        "!", "=", "==", "!=",
        "<", ">", "<=", ">=",
        "*", "/", "+", "-",
        "*=", "/=", "+=", "-=",
        "++", "--", "~", "<<", ">>"
    };

    if (operators.find(name) != operators.end())
    {
        return "operator " + name;
    }

    static std::set<string> reserved_names = {
        "new", "delete"
    };

    if (reserved_names.find(name) != reserved_names.end())
    {
        return "lm_" + name;
    }

    return name;
}

void MethodGen::declare(std::ostream& os) const
{
    os << get_name();
    os << "(";
    for (auto& arg : args)
        arg->declare(os);
    os << ") -> ";
    ret->declare(os);
    os << ";" << endl;
}

void MethodGen::define(std::ostream& os) const
{
    os << get_name();
    os << "(";
    for (auto& arg : args)
        arg->define(os);
    os << ") -> ";
    ret->define(os);
    os << endl;
    os << "{" << endl;
    os << "    ";
    os << "return call(expr, \"" << name << "\"";
    if (args.size() > 0)
    {
        os << ", ";
        for (auto& arg : args)
            arg->invoke(os);
    }
    os << ");" << endl;
    os << "}" << endl;
}

std::unordered_set<ClassGen const*> MethodGen::get_referenced_classes() const
{
    std::unordered_set<ClassGen const*> result;

    for (auto& arg : args)
    {
        if (classes.has_class(arg->get_type()))
        {
            result.insert(arg->get_class());
        }
        else
        {
            cerr << endl << "No class for arg type " << arg->get_type().description() << " of method " << name << endl;
        }
    }

    if (classes.has_class(ret->get_type()))
    {
        result.insert(ret->get_class());
    }
    else
    {
        cerr << endl << "No class for ret type " << ret->get_type().description() << " of method " << name << endl;
    }

    return result;
}

std::unordered_set<TypeIndex> MethodGen::get_referenced_types() const
{
    std::unordered_set<TypeIndex> result;

    for (auto& arg : args)
        result.insert(arg->get_type());

    result.insert(ret->get_type());
    return result;
}
