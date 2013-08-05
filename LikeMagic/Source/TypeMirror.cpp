// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Marshaling/CommonClassImpl.hpp"
#include "LikeMagic/CallTargets/AbstractMethod.hpp"
#include "LikeMagic/Exprs/AbstractExpression.hpp"
#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/CallTargets/BottomPtrTarget.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include "boost/lexical_cast.hpp"

using namespace LikeMagic::Marshaling;
using namespace LikeMagic::CallTargets;
using namespace std;

struct TypeMirror::Impl
{
    AbstractCppObjProxy* class_proxy;  // Allows you to call constructors without already having C++ object
    boost::unordered_map<std::string, TypeMirror const*> bases;
    std::string class_name;
    boost::unordered_map<std::string, std::map<int, AbstractMethod*>> methods;
};


TypeMirror::~TypeMirror() {}

CommonClassImpl::CommonClassImpl(std::string name_, NamespacePath namespace_) :
    class_name(name_),
    ns(namespace_)
{
    if (name_ == "")
        throw std::logic_error("Tried to register class with no name!");

    auto ptr_caster = new BottomPtrTarget();
    add_method("unsafe_ptr_cast", ptr_caster);
}

CommonClassImpl::~CommonClassImpl()
{
    for (auto it=methods.begin(); it != methods.end(); it++)
    {
        std::map<int, AbstractMethod*> const& overloads(it->second);
        for (auto it2=overloads.begin(); it2 != overloads.end(); it2++)
            delete it2->second;
    }
}

void CommonClassImpl::add_method(std::string method_name, AbstractMethod* method)
{
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
        type_system->register_method(this, method_name, method);
    }
}

void CommonClassImpl::suggest_method(std::string method_name, int num_args) const
{
    auto candidates = methods.find(method_name);

    if (candidates == methods.end())
    {
        bool has_c = methods.find(method_name + "_c") != methods.end();
        bool has_nc = methods.find(method_name + "_nc") != methods.end();

        bool has_get = methods.find("get_" + method_name) != methods.end();

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
        else if (has_get)
        {
            std::string msg ="Class " + get_class_name() + " does not have a method named " + method_name
                + " but it does have a field by that name. Fields must be called with a prefix of get_, set_, or ref_ such as: get_" + method_name;
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

AbstractMethod* CommonClassImpl::try_get_method(std::string method_name, int num_args, bool in_base_class) const
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
            AbstractMethod* method = num_iter->second;

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

        AbstractMethod* method = it->second->try_get_method(method_name, num_args, true);
        if (method)
            return method;
    }

    // Lastly return null if not found.
    return 0;
}

bool CommonClassImpl::has_base(TypeMirror const* base) const
{
    for (auto it=bases.begin(); it != bases.end(); it++)
        if (it->second == base || it->second->has_base(base))
            return true;

    return false;
}


void CommonClassImpl::add_base(TypeMirror const* base)
{
    bases[base->get_class_name()] = base;
    type_system->register_base(this, base);
}

std::vector<std::string> CommonClassImpl::get_base_names() const
{
    std::vector<std::string> result;

    for (auto it=bases.begin(); it != bases.end(); it++)
        result.push_back(it->first);

    return result;
}

std::string CommonClassImpl::get_class_name() const
{
    return class_name;
}
