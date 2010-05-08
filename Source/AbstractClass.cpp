#include "LikeMagic/Marshaling/AbstractClass.hpp"
#include "LikeMagic/Marshaling/AbstractCallTargetSelector.hpp"
#include "LikeMagic/SFMO/AbstractExpression.hpp"

using namespace LikeMagic::Marshaling;

void AbstractClass::add_method(std::string method_name, AbstractCallTargetSelector* method)
{
    methods[method_name] = method;
}

AbstractCallTargetSelector* AbstractClass::get_method(std::string method_name) const
{
    if (has_method(method_name))
        return methods.find(method_name)->second;
    else
        for (auto it=bases.begin(); it != bases.end(); it++)
            if (it->second->has_method(method_name))
                return it->second->get_method(method_name);

    throw std::logic_error("Class " + get_class_name() + " does not have method " + method_name);
}


std::vector<BetterTypeInfo> AbstractClass::get_arg_types(std::string method_name) const
{
    return get_method(method_name)->get_arg_types();
}

std::vector<std::string> AbstractClass::get_method_names() const
{
    std::vector<std::string> result;

    for (auto it=methods.begin(); it != methods.end(); it++)
        result.push_back(it->first);

    return result;
}

bool AbstractClass::has_method(std::string method_name) const
{
    return methods.find(method_name) != methods.end();
}

void AbstractClass::add_base_abstr(AbstractClass const* base)
{
    bases[base->get_class_name()] = base;
}

std::vector<std::string> AbstractClass::get_base_names() const
{
    std::vector<std::string> result;

    for (auto it=bases.begin(); it != bases.end(); it++)
        result.push_back(it->first);

    return result;
}

std::string AbstractClass::get_class_name() const
{
    return class_name;
}

AbstractCppObjProxy* AbstractClass::call(AbstractCppObjProxy* target, std::string method_name, std::vector<boost::intrusive_ptr<AbstractExpression>> args) const
{
    return get_method(method_name)->call(target, args);
}
