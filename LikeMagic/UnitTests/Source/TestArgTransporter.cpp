#include "UnitTest++.h"

#include "UnitTests/ArgListHelpers.hpp"

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Interprocess/SharedArgTransporter.hpp"

using namespace std;

using namespace LM;
using namespace LM;

SUITE(TestArgTransporter)
{
    TEST(WriteOneInt)
    {
        char buffer[5];
        *(int*)buffer = 0;  // clear buffer
        buffer[4] = 99;     // sentry value
        ExprPtr arg = Term<int>::create(1234);
        TypeIndex arg_type = get_type_index<int>();
        SharedArgTransporter transporter;
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
        std::vector<LM::ExprPtr> arg_list = make_arg_list<int, int>(1234, 5678);
        TypeInfoList type_list = make_type_list<int, int>();
        SharedArgTransporter transporter;
        transporter.write_args(type_list, buffer, &arg_list[0]);
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
        SharedArgTransporter transporter;
        std::pair<ExprPtr, void*> result =
            transporter.read_value(arg_type, buffer);
        ExprPtr warden;
        int result_value = EvalAs<int>::value(result.first, warden);
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
        SharedArgTransporter transporter;
        ExprPtr warden[2];
        std::vector<ExprPtr> arg_list = transporter.read_args(type_list, buffer);
        int value1 = EvalAs<int>::value(arg_list[0], warden[0]);
        int value2 = EvalAs<int>::value(arg_list[1], warden[1]);
        CHECK_EQUAL(1234, value1);  // check arg written
        CHECK_EQUAL(5678, value2);  // check arg written
        CHECK_EQUAL(99, buffer[8]);        // check sentry
    }
}

