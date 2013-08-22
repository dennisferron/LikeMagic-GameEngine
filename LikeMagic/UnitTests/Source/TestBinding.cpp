#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/BindingMacros.hpp"

using namespace std;

using namespace LM;
using namespace LM;

class BindingTestClass
{
public:
    int FuncInt()
    {
        return 99;
    }
};

struct AddBindingsTestFixture
{
    AddBindingsTestFixture()
    {
        auto& global_ns = type_system->global_namespace();
        LM_CLASS(global_ns, BindingTestClass)
        LM_FUNC(BindingTestClass, (FuncInt))
    }
};

SUITE(TestBinding)
{
    TEST_FIXTURE(AddBindingsTestFixture, CallInt)
    {
    }
}
