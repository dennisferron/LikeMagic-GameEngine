#pragma once

#include "AbstractClass.hpp"
#include "MethodCallGenerator.hpp"
#include "LikeMagic/SFMO/ClassExpr.hpp"
#include "LikeMagic/Marshaling/DummyClass.hpp"

namespace LikeMagic { namespace Utility { struct StaticMethod; }}

// Used in friend declaration.
namespace LikeMagic { class RuntimeTypeSystem; }

namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;
using LikeMagic::Utility::StaticMethod;

class StaticMethods : public DummyClass<StaticMethods>
{
private:
    // No copying or assignment.
    StaticMethods(StaticMethods const&);
    StaticMethods& operator=(StaticMethods const&);

    friend class LikeMagic::RuntimeTypeSystem;
    StaticMethods(std::string name_, AbstractTypeSystem& type_system_) : DummyClass<StaticMethods>(name_, type_system_)
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