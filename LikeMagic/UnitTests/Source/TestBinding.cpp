#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/BindingMacros.hpp"

using namespace std;

using namespace LM;
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
};

struct AddBindingsTestFixture
{
    AddBindingsTestFixture()
    {
        auto& global_ns = type_system->global_namespace();
        LM_CLASS(global_ns, BindingTestClass)
        LM_FUNC(BindingTestClass, (FuncInt)(FuncIntInt))
    }
};

SUITE(TestBinding)
{
    TEST_FIXTURE(AddBindingsTestFixture, CallInt)
    {
        ExprPtr term = Term<BindingTestClass*>::create(new BindingTestClass);
        TypeMirror* type_mirror = type_system->get_class(term->get_type());
        CHECK(type_mirror);
        std::vector<ExprPtr> args;
        auto* method = type_mirror->get_method("FuncInt", args.size());
        CHECK(method);
        ExprPtr result = method->call(term, args);
        CHECK(result);
        CHECK(EvalAs<int>::has_conv(result.get()));
        CHECK_EQUAL(99, EvalAs<int>::value(result));
    }

    TEST_FIXTURE(AddBindingsTestFixture, CallIntInt)
    {
        ExprPtr term = Term<BindingTestClass*>::create(new BindingTestClass);
        TypeMirror* type_mirror = type_system->get_class(term->get_type());
        CHECK(type_mirror);
        std::vector<ExprPtr> args;
        args.push_back(Term<int>::create(100));
        auto* method = type_mirror->get_method("FuncIntInt", args.size());
        CHECK(method);
        ExprPtr result = method->call(term, args);
        CHECK(result);
        CHECK(EvalAs<int>::has_conv(result.get()));
        CHECK_EQUAL(101, EvalAs<int>::value(result));
    }
}
