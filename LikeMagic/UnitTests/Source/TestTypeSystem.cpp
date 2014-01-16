#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/BindingMacros.hpp"

#include "UnitTests/TestHelpers.hpp"

using namespace std;
using namespace LM;

struct ConvTestStruct
{
};

ConvTestStruct* create_test_struct()
{
    return new ConvTestStruct();
}

struct WrapExprTestStruct
{
    bool& is_constructed;
    bool& is_destructed;
};

void add_typesystem_test_bindings()
{
    auto& global_ns = type_system->global_namespace();
    LM_CLASS(global_ns, ConvTestStruct)
    LM_STATIC_FUNC_NAME(global_ns, "create_test_struct", create_test_struct)
}

SUITE(TestTypeSystem)
{
    TEST(TypeIndex)
    {
        CHECK(TypId<ConvTestStruct>::get() == TypId<ConvTestStruct>::get());
        CHECK(!(TypId<ConvTestStruct*>::get() == TypId<ConvTestStruct>::get()));
        CHECK(TypId<ConvTestStruct*>::get() == TypId<ConvTestStruct*>::get());
        CHECK(!(TypId<ConvTestStruct const>::get() == TypId<ConvTestStruct>::get()));
        CHECK(TypId<ConvTestStruct const*>::get() == TypId<ConvTestStruct const*>::get());
    }

    TEST(ConvIntToInt)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(EvalAs<int>::has_conv(term.get()));
        ExprPtr ward;
        CHECK_EQUAL(1234, EvalAs<int>::value(term, ward));
    }

    TEST(ConvIntToDouble)
    {
        ExprPtr term = Term<int>::create(1234);
        CHECK(EvalAs<double>::has_conv(term.get()));
        ExprPtr ward;
        double result = EvalAs<double>::value(term, ward);
        CHECK_CLOSE(1234.0, result, 0.01);
    }

    TEST(HasConvTestStruct)
    {
        ExprPtr term = Term<ConvTestStruct>::create(ConvTestStruct());
        CHECK(EvalAs<ConvTestStruct>::has_conv(term.get()));
    }

    TEST(CreateConvTestStruct)
    {
        TypeMirror const* type_mirror = type_system->get_namespace("");
        ASSERT_NOT_NULL(type_mirror);
        std::vector<ExprPtr> args;
        auto* method = type_mirror->get_method("create_test_struct", args.size());
        ASSERT_NOT_NULL(method);
        ExprPtr result = method->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result);
        CHECK(EvalAs<ConvTestStruct>::has_conv(result.get()));
        ExprPtr ward;
        delete EvalAs<ConvTestStruct*>::value(result, ward);
    }
}
