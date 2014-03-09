// LikeMagic C++ Binding Library
// Copyright 2008-2014 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <string>

#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

class Expr;

class ExprTrackingInfo
{
public:
    Expr* expr;
    void const* data;
    std::string name;

public:
    ExprTrackingInfo();
    ExprTrackingInfo(Expr* const expr_);
    ExprTrackingInfo(Expr* const expr_, std::string name_);
    ExprTrackingInfo(ExprTrackingInfo const& that);
    ExprTrackingInfo& operator =(ExprTrackingInfo const& that);
};

LIKEMAGIC_API void assert_expr(Expr* ptr);

}
