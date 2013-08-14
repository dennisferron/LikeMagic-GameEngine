#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/BindingMacros.hpp"

using namespace std;

using namespace LikeMagic;
using namespace LikeMagic::Exprs;

class BindingTestClass
{
    int FuncInt()
    {
        return 99;
    }
};

struct AddBindingsTestFixture
{
    AddBindingsTestFixture()
    {
        LM_CLASS(BindingTestClass)
        LM_FUNC(BindingTestClass, (FuncInt))
    }
};

SUITE(TestBinding)
{
    TEST_FIXTURE(AddBindingsTestFixture, CallInt)
    {
    }
}
