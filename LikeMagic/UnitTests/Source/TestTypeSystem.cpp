#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"

using namespace std;

using namespace LM;

SUITE(TestTypeSystem)
{
    TEST(HasConvIntToInt)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(has_conv<int>(term.get()));
    }

    TEST(TryConvIntToInt)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK_EQUAL(1234, EvalAs<int>::value(term));
    }

    TEST(HasConvIntToDouble)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(has_conv<double>(term.get()));
    }

    TEST(TryConvIntToDouble)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK_CLOSE(1234.0, EvalAs<double>::value(term), 0.01);
    }
}
