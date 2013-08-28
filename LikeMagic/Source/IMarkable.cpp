#include "LikeMagic/IMarkable.hpp"

namespace LM {

void mark_if_possible(IMarkable const* const* const& obj)
{
    (*obj)->mark();
}

void mark_if_possible(IMarkable const* const& obj)
{
    obj->mark();
}

void mark_if_possible(void const*const& ptr)
{
    // do nothing
}

}
