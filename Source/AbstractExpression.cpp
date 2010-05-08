#include "LikeMagic/SFMO/AbstractExpression.hpp"

namespace LikeMagic { namespace SFMO {

void intrusive_ptr_add_ref(AbstractExpression* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(AbstractExpression* p)
{
    if (!--(p->ref_count))
        delete p;
}

}}
