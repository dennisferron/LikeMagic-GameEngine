#include "UnitTest++.h"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "IoObject.h"

using namespace std;
using namespace Iocaste;
using namespace Iocaste::LMAdapters;

SUITE(TestIoVM)
{
    TEST(CreateIoObject)
    {
        string bootstrap_path = "../../Iocaste/iovm/io/";
        IoVM* vm = new IoVM(bootstrap_path);
        IoState* state = vm->iovm_get_io_state();

        IoObject* bazinga = IoObject_new(state);

        IoObject_setSlot_to_(state->lobby,
            IoState_symbolWithCString_(state, "bazinga"),
            bazinga);


//        IoObject_free(bazinga);

        // This won't work until the problem with the Io object creation is fixed.
        delete vm;
    }
}
