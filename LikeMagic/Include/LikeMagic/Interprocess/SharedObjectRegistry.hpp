#pragma once

#include "LikeMagic/SFMO/AbstractExpression.hpp"

#include "boost/unordered_map.hpp"

namespace LikeMagic { namespace Interprocess {

using ExprPtr = LikeMagic::SFMO::ExprPtr;

typedef int shared_object_handle;

class SharedObjectRegistry
{
private:
    boost::unordered_map<shared_object_handle, ExprPtr> shared_objects;
public:
};

}}
