#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/BindingMacros.hpp"
#include "UnitTests/TestHelpers.hpp"

#include "ns_global.hpp"
#include "LikeMagic/Exprs/call_helper.hpp"

using namespace std;
using namespace LM;
using namespace GameBindings;

SUITE(TestGeneratedInterfaces)
{
    TEST(CallHelper)
    {
        ExprPtr dummy;
        ExprPtr args[]
        {
            dummy
        };
        //call(dummy, "", args, 1);
    }

    TEST(CallTrue)
    {
        auto instance = ScriptUtil::tmp();
        auto result = instance.get_true();
        ExprPtr ward;
        CHECK(EvalAs<bool>::value(result.expr, ward));
    }

    TEST(CallGetString)
    {
        auto instance = ScriptUtil::tmp();
        auto term = Term<string>::create("bailar");
        auto result = instance.get_string({term});
        ExprPtr ward;
        cout << "Got string " << EvalAs<string>::value(result.expr, ward) << endl;
        CHECK(string("bailar") == EvalAs<string>::value(result.expr, ward));
    }
}
