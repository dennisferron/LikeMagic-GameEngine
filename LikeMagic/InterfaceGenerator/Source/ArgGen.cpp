#include "InterfaceGenerator/ArgGen.hpp"
#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"

using namespace LM;

ArgGen::~ArgGen() {}

ArgGen::ArgGen(TypeInfoList args_, int pos_, ClassGenList const& classes_)
    : args(args_), pos(pos_), classes(classes_)
{
}

TypeIndex ArgGen::get_arg_type() const
{
    return args[pos];
}

TypeIndex ArgGen::get_type() const
{
    return args[pos];
}

void ArgGen::write_arg_type(std::ostream& os) const
{
    if (!classes.has_class(get_arg_type()))
    {
        os << "MissingType /* " << get_arg_type().description() << " */ ";
    }
    else
    {
        get_class()->write_name(os);
    }
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
}

void ArgGen::define(std::ostream& os) const
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
    return classes.get_class(get_arg_type());
}
