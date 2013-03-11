// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/BottomPtrExpr.hpp"

namespace LikeMagic { namespace SFMO {

// When IoNil is encountered, it is marshaled as a NullExpr object.
// The type can be converted to any other pointer in TypeConvGraph.
class NullExpr : public Expression<BottomPtrType>
{
private:
    NullExpr() {}

public:
    static boost::intrusive_ptr<Expression<BottomPtrType>> create() { return new NullExpr(); }

    inline virtual BottomPtrType eval() { return NULL; }
    virtual boost::intrusive_ptr<Expression<BottomPtrType>> clone() const { return new NullExpr(); }
    virtual bool is_terminal() const { return true; }

    virtual bool is_null() const { return true; }

    virtual std::string description() const
    {
        return std::string("NULL");
    }

    virtual void mark() const {}
};

}}
