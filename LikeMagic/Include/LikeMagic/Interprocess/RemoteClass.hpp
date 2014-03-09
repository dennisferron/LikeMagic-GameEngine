#pragma once

#include "LikeMagic/Exprs/TypeMirror.hpp"

namespace LM {

using TypeMirror = LM::TypeMirror;

class RemoteClass : TypeMirror
{
private:
    RemoteTypeIndex type_index;

};

}
