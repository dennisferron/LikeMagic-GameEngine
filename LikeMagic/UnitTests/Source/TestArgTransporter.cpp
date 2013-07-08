#include "UnitTest++.h"

#include "UnitTests/TypeSystemInstance.hpp"
#include "UnitTests/ArgListHelpers.hpp"

#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/Interprocess/SharedArgTransporter.hpp"

using namespace std;

using namespace LikeMagic;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Interprocess;

SUITE(TestArgTransporter)
{
    TEST(WriteOneInt)
    {
        char buffer[5];
        *(int*)buffer = 0;  // clear buffer
        buffer[4] = 99;     // sentry value
        ArgList arg_list = make_arg_list<int>(1234);
        TypeInfoList type_list = make_type_list<int>();
        SharedArgTransporter transporter(*type_sys);
        transporter.write_args(type_list, buffer, arg_list);
        CHECK_EQUAL(1234, *(int*)buffer);  // check arg written
        CHECK_EQUAL(99, buffer[4]);        // check sentry
    }
}

