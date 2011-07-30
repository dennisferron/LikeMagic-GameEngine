// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Marshaling/AbstractClass.hpp"
#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/SFMO/AbstractExpression.hpp"
#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/CallTargets/BottomPtrTarget.hpp"

#include "boost/lexical_cast.hpp"

using namespace LikeMagic::Marshaling;
using namespace LikeMagic::CallTargets;
using namespace std;

AbstractClass::AbstractClass(std::string name_, AbstractTypeSystem& type_system_, NamespacePath namespace_) :
    class_name(name_),
    type_system(type_system_),
    ns(namespace_)
{
    if (name_ == "")
        throw std::logic_error("Tried to register class with no name!");

    auto ptr_caster = new BottomPtrTarget(type_system);
    add_method("unsafe_ptr_cast", ptr_caster);
}


AbstractClass::~AbstractClass()
{
    for (auto it=methods.begin(); it != methods.end(); it++)
    {
        std::map<int, AbstractCallTargetSelector*> const& overloads(it->second);
        for (auto it2=overloads.begin(); it2 != overloads.end(); it2++)
            delete it2->second;
    }
}

std::vector<AbstractClass const*> AbstractClass::get_base_classes() const
{
    std::vector<AbstractClass const*> result;

    for (auto it = bases.begin(); it != bases.end(); ++it)
        result.push_back(it->second);

    return result;
}

std::vector<AbstractCallTargetSelector*> AbstractClass::get_methods() const
{
    std::vector<AbstractCallTargetSelector*> result;

    for (auto overloads = methods.begin(); overloads != methods.end(); ++overloads)
        for (auto it = overloads->second.begin(); it != overloads->second.end(); ++it)
            result.push_back(it->second);

    return result;
}


void AbstractClass::add_method(std::string method_name, AbstractCallTargetSelector* method)
{
    method->set_debug_name(method_name);

    int num_args = method->get_arg_types().size();

    if (has_method(method_name, num_args))
    {
        std::cout <<
                class_name + "::" + method_name + " taking " + boost::lexical_cast<std::string>(num_args) + " arguments"
                + " has previously been registered."
                + " (Method names can be overloaded, but only if they have different arg counts. You will have to give one"
                + " of the methods a different name.)" << std::endl;
    }
    else
    {
        // Don't add the same method name if it already has the method.
        method_names.push_back(method_name);
        methods[method_name][num_args] = method;
        type_system.register_method(this, method_name, method);
    }
}

AbstractCallTargetSelector* AbstractClass::get_method(std::string method_name, int num_args) const
{
    AbstractCallTargetSelector* method =
        try_get_method(method_name, num_args);

    if (method)
        return method;
    else
    {
        suggest_method(method_name, num_args);
        return 0;  // never get here
    }
}

void AbstractClass::suggest_method(std::string method_name, int num_args) const
{
    auto candidates = methods.find(method_name);

    if (candidates == methods.end())
    {
        bool has_c = methods.find(method_name + "_c") != methods.end();
        bool has_nc = methods.find(method_name + "_nc") != methods.end();

        if (has_c || has_nc)
        {
            std::string msg = "Class " + get_class_name() + " does not have a method named " + method_name
                    + " but there is a method named "
                    + (has_c? method_name + "_c which is the const version of this method" : "")
                    + (has_c && has_nc? " and " : "")
                    + (has_nc? method_name + "_nc which is the non-const version of this method" : "")
                    + ".  (The _c and _nc notation is needed because C++ can overload methods by const-ness which has no direct equivalent in dynamic languages.)";
            throw std::logic_error(msg);
        }
        else
            throw std::logic_error("Class " + get_class_name() + " does not have any method named " + method_name);
    }
    else
    {
        std::string arg_nums_list = "";

        int count = 0;
        for (auto it=candidates->second.begin(); it!=candidates->second.end(); ++it, ++count)
        {
            if (it->first == num_args)
                throw std::logic_error("Should never get here - the method " + method_name + " with " + boost::lexical_cast<string>(num_args) + " arguments does exist, but for some reason LikeMagic acted as though it did not.");

            if (count > 0)
                arg_nums_list += ", ";

            arg_nums_list += boost::lexical_cast<std::string>(it->first);
        }

        std::string msg = "Class " + get_class_name() + " does have a method called " + method_name
                + " but that method does not have any overload that takes " + boost::lexical_cast<std::string>(num_args)
                + " arguments.  There is/are " + boost::lexical_cast<std::string>(candidates->second.size())
                + " version(s) of that method taking " + arg_nums_list + " argument(s).";
        throw std::invalid_argument(msg);
    }
}

AbstractCallTargetSelector* AbstractClass::try_get_method(std::string method_name, int num_args, bool in_base_class) const
{
    //cout << "try_get_method " << method_name << " " << num_args << endl;

    // First try to find the name and arg number method in this class.
    auto name_iter = methods.find(method_name);
    if (name_iter != methods.end())
    {
        auto overloads = name_iter->second;
        auto num_iter = overloads.find(num_args);
        if (num_iter != overloads.end())
        {
            AbstractCallTargetSelector* method = num_iter->second;

            // Methods that cannot be inherited (like constructors) must not be returned from base class search.
            if (in_base_class && !method->is_inherited())
                return 0;
            else
                return num_iter->second;
        }
    }

    // Second try to find it in the bases.
    for (auto it=bases.begin(); it != bases.end(); it++)
    {
        if (it->second == this)
            throw std::logic_error("The class " + get_class_name() + " is registered as a base of itself!");

        AbstractCallTargetSelector* method = it->second->try_get_method(method_name, num_args, true);
        if (method)
            return method;
    }

    // Lastly return null if not found.
    return 0;
}

TypeInfoList AbstractClass::get_arg_types(std::string method_name, int num_args) const
{
    return get_method(method_name, num_args)->get_arg_types();
}

std::vector<std::string> const& AbstractClass::get_method_names() const
{
    return method_names;
}

bool AbstractClass::has_method(std::string method_name, int num_args) const
{
    auto candidates = methods.find(method_name);

    return
        candidates != methods.end()
    &&
        candidates->second.find(num_args) != candidates->second.end();
}


bool AbstractClass::has_base(AbstractClass const* base) const
{
    for (auto it=bases.begin(); it != bases.end(); it++)
        if (it->second == base || it->second->has_base(base))
            return true;

    return false;
}


void AbstractClass::add_base_abstr(AbstractClass const* base)
{
    if (base == this)
        throw std::logic_error("You tried to add " + get_class_name() + " as a base of itself (not allowed).");

    if (base->has_base(this))
        throw std::logic_error("Inheritance loop:  you executed " + get_class_name() + "->add_base(" + base->get_class_name()
            + ") but " + get_class_name() + " is already an ancestor of " + base->get_class_name() +
            ".  If this add_base is really what you wanted to do then you need to find and remove " + get_class_name() +
            " from the inheritance tree of " + base->get_class_name() );

    bases[base->get_class_name()] = base;
    type_system.register_base(this, base);
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
    return get_method(method_name, args.size())->call(target, args);
}
