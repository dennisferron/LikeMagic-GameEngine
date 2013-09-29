#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/BindingMacros.hpp"
#include "UnitTests/TestHelpers.hpp"

using namespace std;
using namespace LM;

class BindingTestClass
{
public:
    int FuncInt()
    {
        return 99;
    }

    int FuncIntInt(int i)
    {
        return i+1;
    }

    static int StaticFuncIntInt(int i)
    {
        return 2*i;
    }
};

namespace TestNs {
    int NsFuncIntInt(int i)
    {
        return i+10;
    }

    int DiscernNsFuncInt()
    {
        return 11;
    }

    namespace NestedNs {
        int NestedFuncInt()
        {
            return 43;
        }

        int DiscernNsFuncInt()
        {
            return 22;
        }

        namespace TestNs {
            int DiscernNsFuncInt()
            {
                return 33;
            }
        }
    }
}

void add_binding_test_bindings()
{
    auto& global_ns = type_system->global_namespace();
    LM_CLASS(global_ns, BindingTestClass)
    LM_FUNC(BindingTestClass, (FuncInt)(FuncIntInt))
    LM_STATIC_FUNC_NAME(BindingTestClass_LM, "StaticFuncIntInt", BindingTestClass::StaticFuncIntInt)

    auto& test_ns = register_namespace("TestNs", global_ns);
    LM_STATIC_FUNC_NAME(test_ns, "NsFuncIntInt", TestNs::NsFuncIntInt)
    LM_STATIC_FUNC_NAME(test_ns, "DiscernNsFuncInt", TestNs::DiscernNsFuncInt)

    auto& nested_ns = register_namespace("NestedNs", test_ns);
    LM_STATIC_FUNC_NAME(nested_ns, "NestedFuncIntInt", TestNs::NestedNs::NestedFuncInt)
    LM_STATIC_FUNC_NAME(nested_ns, "DiscernNsFuncInt", TestNs::NestedNs::DiscernNsFuncInt)

    auto& nested_test_ns = register_namespace("TestNs", nested_ns);
    LM_STATIC_FUNC_NAME(nested_test_ns, "DiscernNsFuncInt", TestNs::NestedNs::TestNs::DiscernNsFuncInt)
}

SUITE(TestBinding)
{
    TEST(CallInt)
    {
        ExprPtr term = Term<BindingTestClass*>::create(new BindingTestClass);
        TypeMirror* type_mirror = type_system->get_class(term->get_type());
        ASSERT_NOT_NULL(type_mirror);
        std::vector<ExprPtr> args;
        auto* method = type_mirror->get_method("FuncInt", args.size());
        ASSERT_NOT_NULL(method);
        ExprPtr result = method->call(term, &args[0]);
        ASSERT_NOT_NULL(result);
        CHECK(EvalAs<int>::has_conv(result.get()));
        ExprPtr warden;
        CHECK_EQUAL(99, EvalAs<int>::value(result, warden));
    }

    TEST(CallIntInt)
    {
        ExprPtr term = Term<BindingTestClass*>::create(new BindingTestClass);
        TypeMirror* type_mirror = type_system->get_class(term->get_type());
        ASSERT_NOT_NULL(type_mirror);
        std::vector<ExprPtr> args;
        args.push_back(Term<int>::create(100));
        auto* method = type_mirror->get_method("FuncIntInt", args.size());
        ASSERT_NOT_NULL(method);
        ExprPtr result = method->call(term, &args[0]);
        ASSERT_NOT_NULL(result);
        CHECK(EvalAs<int>::has_conv(result.get()));
        ExprPtr warden;
        CHECK_EQUAL(101, EvalAs<int>::value(result, warden));
    }

    TEST(CallStaticIntInt)
    {
        ExprPtr term = Term<BindingTestClass*>::create(new BindingTestClass);
        TypeMirror* type_mirror = type_system->get_class(term->get_type());
        ASSERT_NOT_NULL(type_mirror);
        std::vector<ExprPtr> args;
        args.push_back(Term<int>::create(33));
        auto* method = type_mirror->get_method("StaticFuncIntInt", args.size());
        ASSERT_NOT_NULL(method);
        ExprPtr result = method->call(term, &args[0]);
        ASSERT_NOT_NULL(result);
        CHECK(EvalAs<int>::has_conv(result.get()));
        ExprPtr warden;
        CHECK_EQUAL(66, EvalAs<int>::value(result, warden));
    }

    TEST(CallNsIntInt)
    {
        auto& global_ns = type_system->global_namespace();
        auto& test_ns = register_namespace("TestNs", global_ns);
        TypeMirror* type_mirror = &test_ns; //type_system->get_class(test_ns.get_class_type());
        ASSERT_NOT_NULL(type_mirror);
        std::vector<ExprPtr> args;
        args.push_back(Term<int>::create(11));
        auto* method = type_mirror->get_method("NsFuncIntInt", args.size());
        ASSERT_NOT_NULL(method);
        ExprPtr result = method->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result);
        CHECK(EvalAs<int>::has_conv(result.get()));
        ExprPtr warden;
        CHECK_EQUAL(21, EvalAs<int>::value(result, warden));
    }

    TEST(CallNestedFuncInt)
    {
        auto& global_ns = type_system->global_namespace();
        auto& test_ns = register_namespace("TestNs", global_ns);
        auto& nested_ns = register_namespace("NestedNs", test_ns);
        TypeMirror* type_mirror = &nested_ns; //type_system->get_class(test_ns.get_class_type());
        ASSERT_NOT_NULL(type_mirror);
        std::vector<ExprPtr> args;
        auto* method = type_mirror->get_method("NestedFuncIntInt", args.size());
        ASSERT_NOT_NULL(method);
        ExprPtr result = method->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result);
        CHECK(EvalAs<int>::has_conv(result.get()));
        ExprPtr warden;
        CHECK_EQUAL(43, EvalAs<int>::value(result, warden));
    }

    TEST(DiscernNsFuncInt)
    {
        auto& global_ns = type_system->global_namespace();
        std::vector<ExprPtr> args;

        auto& test_ns = register_namespace("TestNs", global_ns);
        TypeMirror const* type_mirror1 = &test_ns;
        ASSERT_NOT_NULL(type_mirror1);
        auto* method1 = type_mirror1->get_method("DiscernNsFuncInt", args.size());
        ASSERT_NOT_NULL(method1);

        auto& nested_ns = register_namespace("NestedNs", test_ns);
        TypeMirror const* type_mirror2 = &nested_ns; //type_system->get_class(test_ns.get_class_type());
        ASSERT_NOT_NULL(type_mirror2);
        auto* method2 = type_mirror2->get_method("DiscernNsFuncInt", args.size());
        ASSERT_NOT_NULL(method2);

        auto& nested_test_ns = register_namespace("TestNs", nested_ns);
        TypeMirror const* type_mirror3 = &nested_test_ns; //type_system->get_class(test_ns.get_class_type());
        ASSERT_NOT_NULL(type_mirror3);
        auto* method3 = type_mirror3->get_method("DiscernNsFuncInt", args.size());
        ASSERT_NOT_NULL(method3);

        CHECK(type_mirror1 != type_mirror2);
        CHECK(method1 != method2);
        CHECK(type_mirror1 != type_mirror3);
        CHECK(method1 != method3);
        CHECK(type_mirror2 != type_mirror3);
        CHECK(method2 != method3);

        ExprPtr warden;

        ExprPtr result1 = method1->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result1);
        CHECK(EvalAs<int>::has_conv(result1.get()));
        CHECK_EQUAL(11, EvalAs<int>::value(result1, warden));

        ExprPtr result2 = method2->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result2);
        CHECK(EvalAs<int>::has_conv(result2.get()));
        CHECK_EQUAL(22, EvalAs<int>::value(result2, warden));

        ExprPtr result3 = method3->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result3);
        CHECK(EvalAs<int>::has_conv(result3.get()));
        CHECK_EQUAL(33, EvalAs<int>::value(result3, warden));
    }

    TEST(DiscernNsFuncIntUsingGetNamespace)
    {
        std::vector<ExprPtr> args;

        TypeMirror const* type_mirror1 = type_system->get_namespace("::TestNs");
        ASSERT_NOT_NULL(type_mirror1);
        auto* method1 = type_mirror1->get_method("DiscernNsFuncInt", args.size());
        ASSERT_NOT_NULL(method1);

        TypeMirror const* type_mirror2 = type_system->get_namespace("::TestNs::NestedNs"); //type_system->get_class(test_ns.get_class_type());
        ASSERT_NOT_NULL(type_mirror2);
        auto* method2 = type_mirror2->get_method("DiscernNsFuncInt", args.size());
        ASSERT_NOT_NULL(method2);

        TypeMirror const* type_mirror3 = type_system->get_namespace("::TestNs::NestedNs::TestNs"); //type_system->get_class(test_ns.get_class_type());
        ASSERT_NOT_NULL(type_mirror3);
        auto* method3 = type_mirror3->get_method("DiscernNsFuncInt", args.size());
        ASSERT_NOT_NULL(method3);

        CHECK(type_mirror1 != type_mirror2);
        CHECK(method1 != method2);
        CHECK(type_mirror1 != type_mirror3);
        CHECK(method1 != method3);
        CHECK(type_mirror2 != type_mirror3);
        CHECK(method2 != method3);

        ExprPtr warden;

        ExprPtr result1 = method1->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result1);
        CHECK(EvalAs<int>::has_conv(result1.get()));
        CHECK_EQUAL(11, EvalAs<int>::value(result1, warden));

        ExprPtr result2 = method2->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result2);
        CHECK(EvalAs<int>::has_conv(result2.get()));
        CHECK_EQUAL(22, EvalAs<int>::value(result2, warden));

        ExprPtr result3 = method3->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result3);
        CHECK(EvalAs<int>::has_conv(result3.get()));
        CHECK_EQUAL(33, EvalAs<int>::value(result3, warden));
    }
}
