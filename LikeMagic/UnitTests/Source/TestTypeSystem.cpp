#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"

using namespace std;

using namespace LM;
using namespace LM;

SUITE(TestTypeSystem)
{
    TEST(HasConvIntToInt)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(has_conv<int>(term));
    }

    TEST(TryConvIntToInt)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK_EQUAL(1234, try_conv<int>(term)->eval());
    }

    TEST(HasConvIntToDouble)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(has_conv<double>(term));
    }

    TEST(TryConvIntToDouble)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK_CLOSE(1234.0, try_conv<double>(term)->eval(), 0.01);
    }
}
