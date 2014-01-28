// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Mirrors/TypeMirror.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/CallTargets/BottomPtrTarget.hpp"
#include "boost/unordered_map.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include "boost/lexical_cast.hpp"

using namespace LM;
using namespace std;

LIKEMAGIC_API TypeMirror* LM::create_type_mirror(std::string class_name, size_t instance_size, TypeIndex class_type);

class TypeMirrorImpl : private TypeMirror
{
private:
    struct Impl;
    boost::shared_ptr<Impl> impl;

    TypeMirrorImpl(TypeMirrorImpl const&) = delete;
    TypeMirrorImpl& operator =(TypeMirrorImpl const&) = delete;

    friend void suggest_method(TypeMirror& type_, std::string method_name, int num_args);
    friend LIKEMAGIC_API TypeMirror* LM::create_type_mirror(std::string class_name, size_t instance_size, TypeIndex class_type);

public:

    TypeMirrorImpl(std::string class_name, size_t instance_size, TypeIndex class_type);
    virtual ~TypeMirrorImpl();

    virtual std::string get_class_name() const;
    virtual std::string description() const;

    virtual CallTarget* get_method(std::string method_name, int num_args, bool in_base_class=false) const;
    virtual void add_method(std::string method_name, CallTarget* method);

    // support inheritance
    virtual void add_base(TypeMirror const* base);
    virtual bool has_base(TypeMirror const* base) const;

    virtual TypeIndex get_class_type() const;

    virtual size_t get_instance_size() const;

    virtual void suggest_method(std::string method_name, int num_args) const;

    virtual void try_delete(Expr const* expr) const;
    virtual void set_deleter(std::unique_ptr<AbstractTermDeleter const> deleter);
};

LIKEMAGIC_API TypeMirror* LM::create_type_mirror(std::string class_name, size_t instance_size, TypeIndex class_type)
{
    return new TypeMirrorImpl(class_name, instance_size, class_type);
}

struct TypeMirrorImpl::Impl
{
    boost::unordered_map<std::string, TypeMirror const*> bases;
    std::string name;
    boost::unordered_map<std::string, std::map<int, CallTarget*>> methods;
    TypeIndex class_type;
    TypeIndex metaclass_type;
    size_t instance_size;
    std::unique_ptr<AbstractTermDeleter const> term_deleter;
};

TypeMirrorImpl::TypeMirrorImpl(std::string name, size_t instance_size, TypeIndex class_type)
    : impl(new TypeMirrorImpl::Impl)
{
    impl->name = name;
    impl->class_type = class_type;
    impl->instance_size = instance_size;
    impl->term_deleter = nullptr;

    auto ptr_caster = new BottomPtrTarget();
    add_method("unsafe_ptr_cast", ptr_caster);
}

void TypeMirrorImpl::set_deleter(std::unique_ptr<AbstractTermDeleter const> deleter)
{
    impl->term_deleter = std::move(deleter);
}

TypeMirrorImpl::~TypeMirrorImpl()
{
    for (auto it=impl->methods.begin(); it != impl->methods.end(); it++)
    {
        std::map<int, CallTarget*> const& overloads(it->second);
        for (auto it2=overloads.begin(); it2 != overloads.end(); it2++)
            delete it2->second;
    }
}

void TypeMirrorImpl::try_delete(Expr const* expr) const
{
    if (impl->term_deleter == nullptr)
        throw std::logic_error("No deleter registered for " + this->get_class_type().description());

    impl->term_deleter->delete_if_possible(expr->get_value_ptr().as_const);
}

void TypeMirrorImpl::add_method(std::string method_name, CallTarget* method)
{
    int num_args = method->get_arg_types().size();

    if (get_method(method_name, num_args))
    {
        std::cout <<
                impl->name + "::" + method_name + " taking " + boost::lexical_cast<std::string>(num_args) + " arguments"
                + " has previously been registered."
                + " (Method names can be overloaded, but only if they have different arg counts. You will have to give one"
                + " of the methods a different name.)" << std::endl;
    }
    else
    {
        /*
        std::cout << impl->name + "::" + method_name
            + "(" + boost::lexical_cast<std::string>(num_args) + " args)" << std::endl; */
        impl->methods[method_name][num_args] = method;
    }
}

void TypeMirrorImpl::suggest_method(std::string method_name, int num_args) const
{
    auto candidates = impl->methods.find(method_name);

    if (candidates == impl->methods.end())
    {
        bool has_c = impl->methods.find(method_name + "_c") != impl->methods.end();
        bool has_nc = impl->methods.find(method_name + "_nc") != impl->methods.end();

        bool has_get = impl->methods.find("get_" + method_name) != impl->methods.end();

        if (has_c || has_nc)
        {
            std::string msg = description() + " does not have a method named " + method_name
                    + " but there is a method named "
                    + (has_c? method_name + "_c which is the const version of this method" : "")
                    + (has_c && has_nc? " and " : "")
                    + (has_nc? method_name + "_nc which is the non-const version of this method" : "")
                    + ".  (The _c and _nc notation is needed because C++ can overload methods by const-ness which has no direct equivalent in dynamic languages.)";
            throw std::logic_error(msg);
        }
        else if (has_get)
        {
            std::string msg = description() + " does not have a method named " + method_name
                + " but it does have a field by that name. Fields must be called with a prefix of get_, set_, or ref_ such as: get_" + method_name;
            throw std::logic_error(msg);
        }
        else
            throw std::logic_error(description() + " does not have any method named " + method_name);
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

        std::string msg = description() + " does have a method called " + method_name
                + " but that method does not have any overload that takes " + boost::lexical_cast<std::string>(num_args)
                + " arguments.  There is/are " + boost::lexical_cast<std::string>(candidates->second.size())
                + " version(s) of that method taking " + arg_nums_list + " argument(s).";
        throw std::invalid_argument(msg);
    }
}

CallTarget* TypeMirrorImpl::get_method(std::string method_name, int num_args, bool in_base_class) const
{
    // First try to find the name and arg number method in this class.
    auto name_iter = impl->methods.find(method_name);
    if (name_iter != impl->methods.end())
    {
        auto overloads = name_iter->second;
        auto num_iter = overloads.find(num_args);
        if (num_iter != overloads.end())
        {
            CallTarget* method = num_iter->second;

            // Methods that cannot be inherited (like constructors) must not be returned from base class search.
            if (in_base_class && !method->is_inherited())
                return 0;
            else
                return num_iter->second;
        }
    }

    // Second try to find it in the bases.
    for (auto it=impl->bases.begin(); it != impl->bases.end(); it++)
    {
        if (it->second == this)
            throw std::logic_error("The class " + get_class_name() + " is registered as a base of itself!");

        CallTarget* method = it->second->get_method(method_name, num_args, true);
        if (method)
            return method;
    }

    // Lastly return null if not found.
    return 0;
}

bool TypeMirrorImpl::has_base(TypeMirror const* base) const
{
    for (auto it=impl->bases.begin(); it != impl->bases.end(); it++)
        if (it->second == base || it->second->has_base(base))
            return true;

    return false;
}

void TypeMirrorImpl::add_base(TypeMirror const* base)
{
    impl->bases[base->get_class_name()] = base;
}

std::string TypeMirrorImpl::get_class_name() const
{
    return impl->name;
}

std::string TypeMirrorImpl::description() const
{
    TypeInfo info = impl->class_type.get_info();
    string system = info.system;
    string name = impl->name;

    if (system == "namespace")
    {
        if (name == "")
            return "Global namespace";
        else
            return "C++ namespace " + name;
    }
    else if (system == "C++")
        return "C++ class " + name;
    else
        return name + "( of type " + info.description() + ")";
}

size_t TypeMirrorImpl::get_instance_size() const
{
    return impl->instance_size;
}

TypeIndex TypeMirrorImpl::get_class_type() const
{
    return impl->class_type;
}
