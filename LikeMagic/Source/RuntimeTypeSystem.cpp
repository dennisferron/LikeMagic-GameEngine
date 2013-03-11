// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "LikeMagic/NamespacePath.hpp"

#include "LikeMagic/TypeConv/StringConv.hpp"
#include "LikeMagic/TypeConv/IteratorConv.hpp"

#include "LikeMagic/Utility/UserMacros.hpp"

#include "LikeMagic/ScriptUtil.hpp"

#include <sstream>

using namespace LikeMagic;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::TypeConv;
using namespace LikeMagic::Utility;

using namespace std;

StaticMethods& RuntimeTypeSystem::register_functions(NamespacePath const ns)
{
    TypeIndex type = ns.get_type();
    //cout << "Register functions type index = " << type.get_id() << " " << type.describe() << endl;

    if (has_class(type))
        return cast_existing_class<StaticMethods>(type, true);
    else
    {
        StaticMethods* result = new StaticMethods(*this, ns);
        add_class(result->get_type(), result);
        result->add_base_abstr(proxy_methods);
        return *result;
    }
}

RuntimeTypeSystem::RuntimeTypeSystem()
{
}
