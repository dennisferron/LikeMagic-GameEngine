#include "InterfaceGenerator/RetGen.hpp"

using namespace LM;

RetGen::RetGen(TypeIndex ret_type_, std::unordered_map<TypeIndex, ClassGen const*> const& classes_)
    : ret_type(ret_type_), classes(classes_)
{
}

void RetGen::declare(std::ostream& os) const
{

}

void RetGen::define(std::ostream& os) const
{

}

ClassGen const* RetGen::get_class() const
{
    return classes.find(ret_type)->second;
}
