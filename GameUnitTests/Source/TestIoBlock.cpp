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
        virtual ~MarkableMock() {}

        mutable bool has_been_marked = false;
        virtual void mark() const
        {
            has_been_marked = true;
        }
    };
/*
    TEST(MarkIoBlock)
    {
        string io_code = "retainIt := Object clone; block(markObj, retainIt someSlot := markObj )";
        BlockPtr block = io_vm->get_expr<BlockPtr>(io_code);
        MarkableMock* markObj = new MarkableMock();
        block->operator()<IMarkable*>(markObj);
        block->mark();
        CHECK(markObj->has_been_marked);

        if (markObj->has_been_marked)
            cout << "Success!  Block retained object has been marked!" << endl;

        // Erase the reference to the mock object inside the block inside IoVM.
        block->operator()<void*>(nullptr);
        io_vm->do_string("removeSlot(\"retainIt\"");
        delete markObj;
    }
*/
}
