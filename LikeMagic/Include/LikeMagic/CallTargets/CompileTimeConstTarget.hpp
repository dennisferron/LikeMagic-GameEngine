// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"

#include "LikeMagic/SFMO/CppObjProxy.hpp"
#include "LikeMagic/SFMO/Term.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename ValueT, ValueT RetValue>
class CompileTimeConstTarget : public AbstractCallTargetSelector
{
public:

    CompileTimeConstTarget(AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        return CppObjProxy<ValueT&, true>::create(Term<ValueT, true>::create(RetValue), type_system)
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<>());
    }

    // Not inherited because the size of a base class may be smaller than that of a derived class!
    virtual bool is_inherited() const { return false; }
};


}}
