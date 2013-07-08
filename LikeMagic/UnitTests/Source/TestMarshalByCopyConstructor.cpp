#include "UnitTest++.h"

#include "UnitTests/TypeSystemInstance.hpp"
#include "UnitTests/ArgListHelpers.hpp"

#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/Interprocess/MarshalByCopyConstructor.hpp"

using namespace std;

using namespace LikeMagic;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Interprocess;

SUITE(TestMarshalByCopyConstructor)
{
    TEST(MarshalOneInt)
    {
        char buffer[5];
        *(int*)buffer = 0;  // clear buffer
        buffer[4] = 99;     // sentry value
        ExprPtr term = Term<int, true>::create(1234);
        MarshalByCopyConstructor<int> marshaller(*type_sys);
        marshaller.write(buffer, term);
        CHECK_EQUAL(1234, *(int*)buffer);  // check arg written
        CHECK_EQUAL(99, buffer[4]);        // check sentry
    }
}


