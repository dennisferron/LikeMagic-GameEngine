
#include "UnitTest++.h"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/BindingMacros.hpp"

#include "UnitTests/TestHelpers.hpp"

#include "IoObject.h"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

#include "Iocaste/MapIntToIoObject.hpp"

#include <map>

using namespace std;
using namespace LM;
using namespace Iocaste;

extern Iocaste::LMAdapters::IoVM* io_vm;

SUITE(TestMapIntIoObject)
{
    TEST(TermAtPut)
    {
        ExprPtr term = Term<MapIntToIoObject>::create(MapIntToIoObject());
        TypeMirror const* type_mirror = type_system->get_class(term->get_type());
        ASSERT_NOT_NULL(type_mirror);

        std::vector<ExprPtr> args1;
        args1.push_back(Term<int>::create(11));
        args1.push_back(Term<IoObject*>::create(nullptr));

        auto* method1 = type_mirror->get_method("atPut", args1.size());
        ASSERT_NOT_NULL(method1);

        ExprPtr result1 = method1->call(term, &args1[0]);

        std::vector<ExprPtr> args2;
        args2.push_back(Term<int>::create(11));

        auto* method2 = type_mirror->get_method("at", args2.size());
        ASSERT_NOT_NULL(method2);

        ExprPtr result2 = method2->call(term, &args2[0]);
        ASSERT_NOT_NULL(result2);
        ExprPtr ward;
        CHECK_EQUAL((void*)nullptr, (void*)EvalAs<IoObject*>::value(result2, ward));
    }

    TEST(IoCodeAtPut)
    {
        std::string result = io_vm->get_expr<std::string>(std::string() +
            "m := namespace MapIntToIoObject tmp; " +
            "a := 99;" +
            "o := Object clone do( v := \"y\" ); "
            "m atPut(a, o); " +
            "r := m at(a); " +
            "r v"
        );
        cout << endl;
        cout << endl;
        cout << "!!!!!!!!! Result is: " << result << endl;
        cout << endl;
        cout << endl;
    }
}
