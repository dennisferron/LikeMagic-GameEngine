#include "UnitTest++.h"
#include "UnitTests/ArgListHelpers.hpp"

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Interprocess/MarshalByCopyConstructor.hpp"

using namespace std;

using namespace LM;
using namespace LM;

/*
SUITE(TestMarshalByCopyConstructor)
{
    TEST(WriteOneInt)
    {
        char buffer[5];
        *(int*)buffer = 0;  // clear buffer
        buffer[4] = 99;     // sentry value
        ExprPtr term = Term<int>::create(1234);
        MarshalByCopyConstructor<int> marshaller();
        marshaller.write(buffer, term);
        CHECK_EQUAL(1234, *(int*)buffer);  // check arg written
        CHECK_EQUAL(99, buffer[4]);        // check sentry
    }

    TEST(ReadOneInt)
    {
        char buffer[5];
        *(int*)buffer = 1234;  // set buffer
        buffer[4] = 99;     // sentry value
        MarshalByCopyConstructor<int> marshaller();
        ExprPtr result_term = marshaller.read(buffer);
        int result_value = try_conv<int>(result_term)->eval();
        CHECK_EQUAL(1234, result_value);  // check arg written
        CHECK_EQUAL(99, buffer[4]);        // check sentry
    }
}
*/
