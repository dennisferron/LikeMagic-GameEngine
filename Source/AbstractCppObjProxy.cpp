// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/SFMO/AbstractCppObjProxy.hpp"
#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Marshaling/AbstractClass.hpp"

using namespace LikeMagic::Marshaling;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;

std::string AbstractCppObjProxy::get_class_name() const
{
    return type_system.get_class_name(get_type());
}

std::string AbstractCppObjProxy::get_base_names() const
{
    std::vector<std::string> names = type_system.get_base_names(get_type());
    std::string total;
    for (auto it=names.begin(); it != names.end(); ++it)
        total += *it + " ";
    return total;
}

AbstractCppObjProxy* AbstractCppObjProxy::call(std::string method_name, ArgList args)
{
    auto method = get_method(method_name, args.size());
    return call(method, args);
}

AbstractClass const* AbstractCppObjProxy::get_class() const
{
    return class_;
}

AbstractCppObjProxy* AbstractCppObjProxy::call(AbstractCallTargetSelector* method, ArgList args)
{
    if (!method)
        throw std::logic_error("Method is null.");

    auto proxy1 = method->call(this, args);

    if (!proxy1)
    {
        return NULL;
    }
    else if (proxy1->is_lazy() || proxy1->is_terminal() || proxy1->disable_to_script_conv())
    {
        return proxy1;
    }
    else
    {
        // eagerly evaluate the first result, delete that proxy, and return the new result instead.
        auto proxy2 = proxy1->eval();
        delete proxy1;
        return proxy2;
    }
}


TypeInfoList AbstractCppObjProxy::get_arg_types(std::string method_name, int num_args) const
{
    return type_system.get_arg_types(get_type(), method_name, num_args);
}


AbstractCallTargetSelector* AbstractCppObjProxy::get_method(std::string method_name, int num_args) const
{
    if (!class_)
        throw std::logic_error("This type of proxy has no associated C++ class.");

    return class_->get_method(method_name, num_args);
}


AbstractCallTargetSelector* AbstractCppObjProxy::try_get_method(std::string method_name, int num_args) const
{
    if (!class_)
        throw std::logic_error("This type of proxy has no associated C++ class.");

    return class_->try_get_method(method_name, num_args);
}

void AbstractCppObjProxy::suggest_method(std::string method_name, int num_args) const
{
    if (!class_)
        throw std::logic_error("This type of proxy has no associated C++ class.");

    class_->suggest_method(method_name, num_args);
}


void AbstractCppObjProxy::check_magic()
{
    if (!this)
    {
        std::cout << "AbstractCppObjProxy:  'this' was null" << std::endl;
        throw std::logic_error("AbstractCppObjProxy:  'this' was null");
    }

    long magic = this->magic_number;
    if (magic == 0xFFFFFFFF)
    {
        std::cout << "check_magic: passed a CppObjProxy that has been deleted " << std::setbase(16) << magic
            << " this = " << this;
        throw std::logic_error("Deleted CppObjProxy used.");
    }
    else if (magic != 0xCAFEBABE)
    {
        std::cout << "Object was supposed to be an CppObjProxy, but is not.  Magic number was " << std::setbase(16) << magic
            << " this = " << this;
        throw std::logic_error("Object was supposed to be an CppObjProxy, but is not.");
    }
}
