// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/AbstractTypeSystem.hpp"

using namespace LikeMagic;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Marshaling;
using namespace LikeMagic::CallTargets;

#include <iostream>
using namespace std;

AbstractCallTargetSelector::AbstractCallTargetSelector(AbstractTypeSystem const& type_system_)
    : type_system(type_system_)
{

}


AbstractCallTargetSelector::~AbstractCallTargetSelector()
{
}

// Some methods (like constructors) should not be inherited.
bool AbstractCallTargetSelector::is_inherited() const
{
    return true;
}

void AbstractCallTargetSelector::set_expr_debug_name(ExprPtr arg) const
{

    if (type_system.has_conv<DebugInfo&>(arg))
    {
        const char* blah = get_debug_name().c_str();
        cout << "Setting debug name " << get_debug_name() << endl;
        type_system.try_conv<DebugInfo&>(arg)->eval().set_debug_name(this->get_debug_name());
    }

}


