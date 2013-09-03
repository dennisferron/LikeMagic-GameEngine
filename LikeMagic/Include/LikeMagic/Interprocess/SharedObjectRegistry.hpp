#pragma once

#include "LikeMagic/Exprs/Expr.hpp"

#include "boost/unordered_map.hpp"

namespace LM {

using ExprPtr = LM::ExprPtr;

typedef int shared_object_handle;

class SharedObjectRegistry
{
private:
    boost::unordered_map<shared_object_handle, ExprPtr> shared_objects;
public:
};

}
