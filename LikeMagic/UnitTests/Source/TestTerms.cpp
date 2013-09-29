#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/BindingMacros.hpp"

#define ASSERT_NOT_NULL(value) \
    CHECK((value) != nullptr); \
    if ((value) == nullptr) \
        throw std::logic_error(std::string("Pointer should not be null: ") + #value);

using namespace std;
using namespace LM;

struct ConstructorTestClass
{
    int value;
    ConstructorTestClass(int value_) : value(value_) {}
};

struct DestructorTestClass
{
    bool& output;

    DestructorTestClass(bool& output_) : output(output_) {}
    ~DestructorTestClass()
    {
        output = true;
    }
};

void add_term_test_bindings()
{
    auto& global_ns = type_system->global_namespace();
    LM_CLASS(global_ns, ConstructorTestClass)
    LM_CONSTR(ConstructorTestClass, "new", int)
    LM_CLASS(global_ns, DestructorTestClass)
}

void create_and_destroy(bool& output)
{
    ExprPtr term = Term<DestructorTestClass const*>
        ::create(new DestructorTestClass(output));
    term->set_auto_delete_ptr(true);
    // ...and let it go out of scope.
}

SUITE(TestTerms)
{
    TEST(CallIntConstrutor)
    {
        TypeMirror const* global_ns = type_system->get_namespace("");
        ASSERT_NOT_NULL(global_ns);

        auto* class_slot = global_ns->get_method("ConstructorTestClass", 0);
        ASSERT_NOT_NULL(class_slot);

        std::vector<ExprPtr> constr_args;
        ExprPtr class_expr = class_slot->call(nullptr, &constr_args[0]);
        ASSERT_NOT_NULL(class_expr);

        TypeMirror const* class_mirror = type_system->get_class(class_expr->get_type());
        ASSERT_NOT_NULL(class_mirror);

        std::vector<ExprPtr> args;
        args.push_back(Term<int>::create(99));
        auto* method = class_mirror->get_method("new", args.size());
        ASSERT_NOT_NULL(method);
        ExprPtr result = method->call(nullptr, &args[0]);
        ASSERT_NOT_NULL(result);
        CHECK(EvalAs<ConstructorTestClass>::has_conv(result.get()));
        ExprPtr warden;
        CHECK_EQUAL(99, EvalAs<ConstructorTestClass>::value(result, warden).value);
        delete EvalAs<ConstructorTestClass const*>::value(result, warden);
    }

    TEST(TermDestructor)
    {
        bool did_it_work = false;
        create_and_destroy(did_it_work);
        CHECK(did_it_work);
    }
}
