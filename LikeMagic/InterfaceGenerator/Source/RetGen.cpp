#include "InterfaceGenerator/RetGen.hpp"
#include "InterfaceGenerator/ClassGen.hpp"
#include "InterfaceGenerator/ClassGenList.hpp"

using namespace LM;

RetGen::~RetGen() {}

RetGen::RetGen(TypeIndex ret_type_, ClassGenList const& classes_)
    : ret_type(ret_type_), classes(classes_)
{
}

void RetGen::declare(std::ostream& os) const
{
    if (!classes.has_class(ret_type))
    {
        os << "Missing<" << ret_type.description() << ">";
    }
    else
    {
        get_class()->write_name(os);
    }
}

void RetGen::define(std::ostream& os) const
{
    if (!classes.has_class(ret_type))
    {
        os << "Missing<" << ret_type.description() << ">";
    }
    else
    {
        get_class()->write_name(os);
    }
}

ClassGen const* RetGen::get_class() const
{
    return classes.get_class(ret_type);
}

TypeIndex RetGen::get_type() const
{
    return ret_type;
}
