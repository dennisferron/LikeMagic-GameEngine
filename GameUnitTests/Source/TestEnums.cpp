#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/BindingMacros.hpp"

#include "UnitTests/TestHelpers.hpp"

#include <iostream>

using namespace std;
using namespace LM;

namespace DummyNs {

enum Beers
{
    PaleAle = 11,
    Stout = 22,
    Porter = 33
};

}

using namespace DummyNs;

void add_enum_test_bindings()
{
    auto& global_ns = type_system->global_namespace();
    LM_ENUM(global_ns, Beers)
    LM_ENUM_VALUES(global_ns, (PaleAle)(Stout)(Porter))
}

ExprPtr try_get_enum(string name)
{
    TypeMirror const* type_mirror = type_system->get_namespace("");
    ASSERT_NOT_NULL(type_mirror);
    std::vector<ExprPtr> args;
    auto* method = type_mirror->get_method(name, args.size());
    ASSERT_NOT_NULL(method);
    ExprPtr result = method->call(nullptr, &args[0]);
    ASSERT_NOT_NULL(result);

    cout << "Result of " << name << " expr is " << result->description() << endl;

    CHECK(EvalAs<Beers>::has_conv(result.get()));
    return result;
}

SUITE(TestEnums)
{
    TEST(EnumTerm)
    {
        ExprPtr expr = Term<Beers>::create(PaleAle);
        CHECK(EvalAs<Beers>::has_conv(expr.get()));
        ExprPtr ward;
        Beers value = EvalAs<Beers>::value(expr, ward);
        CHECK_EQUAL(PaleAle, value);
    }

    TEST(EnumTermValue)
    {
        ExprPtr expr = Term<Beers>::create(PaleAle);
        CHECK(EvalAs<Beers>::has_conv(expr.get()));
        TypeIndex exprType = expr->get_type();
        TypeMirror* type_mirror = type_system->get_class(exprType);
        ASSERT_NOT_NULL(type_mirror);
        auto* method = type_mirror->get_method("value", 0);
        ASSERT_NOT_NULL(method);
        std::vector<ExprPtr> args;
        ExprPtr result = method->call(expr, &args[0]);
        ExprPtr ward;
        int value = EvalAs<int>::value(result, ward);
        CHECK_EQUAL((int)PaleAle, value);
    }

    TEST(EnumTermAsString)
    {
        ExprPtr expr = Term<Beers>::create(PaleAle);
        CHECK(EvalAs<Beers>::has_conv(expr.get()));
        TypeIndex exprType = expr->get_type();
        TypeMirror* type_mirror = type_system->get_class(exprType);
        ASSERT_NOT_NULL(type_mirror);
        auto* method = type_mirror->get_method("asString", 0);
        ASSERT_NOT_NULL(method);
        std::vector<ExprPtr> args;
        ExprPtr result = method->call(expr, &args[0]);
        ExprPtr ward;
        string name = EvalAs<string>::value(result, ward);
        CHECK_EQUAL("11", name);
    }

    TEST(EnumValues)
    {
        ExprPtr ward;

        ExprPtr value1 = try_get_enum("PaleAle");
        Beers b1 = EvalAs<Beers>::value(value1, ward);
        int i1 = (int)b1;
        CHECK_EQUAL(PaleAle, b1);
    }
}
