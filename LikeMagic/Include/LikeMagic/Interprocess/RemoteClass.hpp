#pragma once

#include "LikeMagic/Exprs/TypeMirror.hpp"

namespace LikeMagic { namespace Interprocess {

using TypeMirror = LikeMagic::Exprs::TypeMirror;

class RemoteClass : TypeMirror
{
private:
    RemoteTypeIndex type_index;

};

}}
