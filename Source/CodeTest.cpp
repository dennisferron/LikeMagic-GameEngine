
#include "LikeMagic/IMarkable.hpp"

using namespace LikeMagic;

class TestClass : public IMarkable
{
    virtual void mark() const { }
};

void test()
{
    IMarkable::markIfMarkable(new TestClass);
}
