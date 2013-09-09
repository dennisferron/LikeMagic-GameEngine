#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"

using namespace std;

using namespace LM;

SUITE(TestTypeSystem)
{
    TEST(ConvIntToInt)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(EvalAs<int>::has_conv(term.get()));
        CHECK_EQUAL(1234, EvalAs<int>::value(term));
    }

    TEST(ConvIntToDouble)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(EvalAs<double>::has_conv(term.get()));
        CHECK_CLOSE(1234.0, EvalAs<double>::value(term), 0.01);
    }
}
