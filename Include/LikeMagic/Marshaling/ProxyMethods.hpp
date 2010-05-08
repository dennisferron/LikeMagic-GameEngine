#pragma once

#include "AbstractClass.hpp"
#include "ProxyMethodSelector.hpp"

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;

class ProxyMethods : public AbstractClass
{
private:

    // No unnamed ProxyMethods, no passing ProxyMethods copies around.
    ProxyMethods();
    ProxyMethods(const ProxyMethods&);

    friend class LikeMagic::RuntimeTypeSystem;
    ProxyMethods(std::string name_, AbstractTypeSystem& type_system_) : AbstractClass(name_, type_system_)
    {
    }

public:

    // Used to declare the default methods that operate on the proxy object.
    template <typename F>
    void bind_method(std::string method_name, F f)
    {
        auto calltarget = new ProxyMethodSelector<F>(f, type_system);
        add_method(method_name, calltarget);
    }
};


}}