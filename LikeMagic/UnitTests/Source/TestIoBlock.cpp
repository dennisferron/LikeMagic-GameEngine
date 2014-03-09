#include "UnitTest++.h"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "IoObject.h"
#include "Iocaste/LikeMagicAdapters/ToIoObjectExpr.hpp"

#include "UnitTests/TestHelpers.hpp"

using namespace std;
using namespace Iocaste;
using namespace Iocaste::LMAdapters;
using namespace LM;

extern Iocaste::LMAdapters::IoVM* io_vm;

SUITE(TestIoBlock)
{
    TEST(IoBlock)
    {
        string io_code = "block(a, return a+11)";
        BlockPtr block = io_vm->get_expr<BlockPtr>(io_code);
        CHECK_EQUAL(33, block->eval<int>(22));
    }

    struct MarkableMock : public IMarkable
    {
        mutable bool has_been_marked = false;
        virtual void mark() const
        {
            has_been_marked = true;
        }
    };

    TEST(MarkIoBlock)
    {
        string io_code = "retainIt := Object clone; block(markObj, retainIt someSlot := markObj )";
        BlockPtr block = io_vm->get_expr<BlockPtr>(io_code);
        MarkableMock markObj;
        block->operator()<IMarkable const&>(markObj);
        block->mark();
        CHECK(markObj.has_been_marked);
    }
}
