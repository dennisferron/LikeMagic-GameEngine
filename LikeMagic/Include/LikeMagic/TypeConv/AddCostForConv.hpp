// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeConv/ConvertibleTo.hpp"
#include "LikeMagic/SFMO/Trampoline.hpp"

#include "boost/lexical_cast.hpp"

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

class AddCostForConv : public AbstractTypeConverter
{
private:
    struct UniqueTypeInfo
    {
        UniqueTypeInfo(AddCostForConv* instance)
        {

        }
    };

    int cost;
    TypeIndex unique_index;

    AddCostForConv(int cost_)
    {

    }

public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return expr;
    }

    TypeIndex get_unique_type_index() const { return unique_index; }

    virtual std::string describe() const { return "Add Conv Cost " + boost::lexical_cast<std::string>(cost); }
};


}}
