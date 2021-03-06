#include "UnitTest++.h"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "IoObject.h"
#include "Iocaste/LikeMagicAdapters/ToIoObjectExpr.hpp"

#include "UnitTests/TestHelpers.hpp"

using namespace std;
using namespace Iocaste;
using namespace Iocaste::LMAdapters;

extern Iocaste::LMAdapters::IoVM* io_vm;

SUITE(TestIoVM)
{
    TEST(RoundTripFloat)
    {
        float result = io_vm->get_expr<float>("namespace ScriptUtil get_float(1.2)");
        CHECK_CLOSE(1.2, result, 0.01);
    }

    TEST(RoundTripString)
    {
        string result = io_vm->get_expr<string>("namespace ScriptUtil get_string(\"hippopotamus\")");
        CHECK_EQUAL("hippopotamus", result);
    }

    TEST(StringToScript)
    {
        string result = io_vm->get_expr<string>("namespace ScriptUtil get_string(\"hippopotamus\") type");
        CHECK_EQUAL("Sequence", result);
    }

    TEST(FloatToScript)
    {
        string result = io_vm->get_expr<string>("namespace ScriptUtil get_float(1.2) type");
        CHECK_EQUAL("Number", result);
    }

    TEST(HasDoubleToIoConv)
    {
        ExprPtr from_expr = Term<double>::create(1.234);
        TypeIndex to_io_type = ToIoTypeInfo::create_index();
        bool has_type_sys_conv = type_system->has_conv(from_expr->get_type(), to_io_type);
        CHECK(has_type_sys_conv);
    }

    TEST(HasStringToIoConv)
    {
        ExprPtr from_expr = Term<string>::create("beluga whale");
        TypeIndex to_type = ToIoTypeInfo::create_index();
        TypeIndex from_type = from_expr->get_type();
        bool has_type_sys_conv = type_system->has_conv(from_type, to_type);
        //cout << "has_type_sys_conv " << has_type_sys_conv << " from " << from_type.description() << " " << from_type.get_id() << " to " << to_type.description() << " " << to_type.get_id() << endl;
        CHECK(has_type_sys_conv);
    }

    TEST(HasNamespaceStd)
    {
        string io_code = "namespace std";
        auto expr = io_vm->get_abs_expr(io_code);
        ASSERT_NOT_NULL(expr);
        TypeInfo expr_type = expr->get_type().get_info();
        CHECK_EQUAL("namespace", expr_type.system);
        CHECK_EQUAL("::std", expr_type.name);
    }

    TEST(FromIoNilToPtr)
    {
        string io_code = "nil";
        auto expr = io_vm->get_abs_expr(io_code);
        CHECK(EvalAs<int*>::has_conv(expr.get()));
        ExprPtr ward;
        CHECK_EQUAL((int*)nullptr, EvalAs<int*>::value(expr, ward));
    }
}
