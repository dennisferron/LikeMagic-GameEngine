#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/ClassGen.hpp"

using namespace LM;

ArgGen::ArgGen(TypeInfoList args_, int pos_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_)
    : args(args_), pos(pos_), classes(classes_)
{
}

TypeIndex ArgGen::get_arg_type() const
{
    return args[pos];
}

void ArgGen::write_arg_type(std::ostream& os) const
{
    get_class()->write_name(os);
}

void ArgGen::write_arg_name(std::ostream& os) const
{
    os << "arg";
    os << pos;
}

void ArgGen::declare(std::ostream& os) const
{
    if (pos > 0)
        os << ", ";

    write_arg_type(os);
    os << " ";
    write_arg_name(os);
}

void ArgGen::invoke(std::ostream& os) const
{
    write_arg_name(os);
}

ClassGen const* ArgGen::get_class() const
{
    return classes.find(get_arg_type())->second;
}
