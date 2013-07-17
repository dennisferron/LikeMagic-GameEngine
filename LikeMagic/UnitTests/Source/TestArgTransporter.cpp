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
        ExprPtr arg = Term<int, true>::create(1234);
        TypeIndex arg_type = get_type_index<int>();
        SharedArgTransporter transporter(*type_sys);
        void* next_location = transporter.write_value(arg_type, buffer, arg);
        CHECK_EQUAL(1234, *(int*)buffer);  // check arg written
        CHECK_EQUAL(99, buffer[4]);        // check sentry
        CHECK_EQUAL((void*)&(buffer[4]), next_location);
    }

    TEST(WriteIntList)
    {
        char buffer[9];
        *(int*)&(buffer[0]) = 0;  // clear buffer
        *(int*)&(buffer[4]) = 0;  // clear buffer
        buffer[8] = 99;             // sentry value
        ArgList arg_list = make_arg_list<int, int>(1234, 5678);
        TypeInfoList type_list = make_type_list<int, int>();
        SharedArgTransporter transporter(*type_sys);
        transporter.write_args(type_list, buffer, arg_list);
        CHECK_EQUAL(1234, *(int*)&(buffer[0]));  // check arg written
        CHECK_EQUAL(5678, *(int*)&(buffer[4]));  // check arg written
        CHECK_EQUAL(99, buffer[8]);        // check sentry
    }

    TEST(ReadOneInt)
    {
        char buffer[5];
        *(int*)buffer = 1234;   // set buffer
        buffer[4] = 99;         // sentry value
        TypeIndex arg_type = get_type_index<int>();
        SharedArgTransporter transporter(*type_sys);
        std::pair<ExprPtr, void*> result =
            transporter.read_value(arg_type, buffer);
        int result_value = type_sys->try_conv<int>(result.first)->eval();
        CHECK_EQUAL(1234, result_value);  // check arg written
        CHECK_EQUAL(99, buffer[4]);        // check sentry
        CHECK_EQUAL((void*)&(buffer[4]), result.second);
    }

    TEST(ReadIntList)
    {
        char buffer[9];
        *(int*)&(buffer[0]) = 1234;  // set buffer
        *(int*)&(buffer[4]) = 5678;  // set buffer
        buffer[8] = 99;             // sentry value
        TypeInfoList type_list = make_type_list<int, int>();
        SharedArgTransporter transporter(*type_sys);
        ArgList arg_list = transporter.read_args(type_list, buffer);
        int value1 = type_sys->try_conv<int>(arg_list[0])->eval();
        int value2 = type_sys->try_conv<int>(arg_list[1])->eval();
        CHECK_EQUAL(1234, value1);  // check arg written
        CHECK_EQUAL(5678, value2);  // check arg written
        CHECK_EQUAL(99, buffer[8]);        // check sentry
    }
}

