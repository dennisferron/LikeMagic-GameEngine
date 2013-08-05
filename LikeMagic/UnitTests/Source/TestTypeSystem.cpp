#include "UnitTest++.h"

#include "UnitTests/TypeSystemInstance.hpp"
#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"

using namespace std;

using namespace LikeMagic;
using namespace LikeMagic::Exprs;

SUITE(TestTypeSystem)
{
    TEST(HasConvIntToInt)
    {
        ExprPtr term = Term<int, true>::create(1234);
        CHECK(type_sys->has_conv<int>(term));
    }

    TEST(TryConvIntToInt)
    {
        ExprPtr term = Term<int, true>::create(1234);
        CHECK_EQUAL(1234, type_sys->try_conv<int>(term)->eval());
    }

    TEST(HasConvIntToDouble)
    {
        ExprPtr term = Term<int, true>::create(1234);
        CHECK(type_sys->has_conv<double>(term));
    }

    TEST(TryConvIntToDouble)
    {
        ExprPtr term = Term<int, true>::create(1234);
        CHECK_CLOSE(1234.0, type_sys->try_conv<double>(term)->eval(), 0.01);
    }
}
