#pragma once

#include "AbstractClass.hpp"
#include "MethodCallGenerator.hpp"

namespace LikeMagic { namespace Utility { struct StaticMethod; }}

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::StaticMethod;

class StaticMethods : public AbstractClass
{
private:

    // No unnamed StaticMethods, no passing StaticMethods copies around.
    StaticMethods();
    StaticMethods(const StaticMethods&);

    friend class LikeMagic::RuntimeTypeSystem;
    StaticMethods(std::string name_, AbstractTypeSystem& type_system_) : AbstractClass(name_, type_system_)
    {
    }

public:

    template <typename F>
    void bind_method(std::string method_name, F f)
    {
        auto calltarget = new MethodCallGenerator<StaticMethod, F>(f, type_system);
        add_method(method_name, calltarget);
    }
};


}}