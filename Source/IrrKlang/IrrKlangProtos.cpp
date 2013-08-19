// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/IrrKlang/Protos.hpp"

#ifndef USE_IRRKLANG

// Replace protos with empty dummy function.
using namespace Iocaste::LikeMagicAdapters;
namespace Bindings { namespace IrrKlang {
void add_protos(IoVM& vm) {}
}}

#else

#include "irrKlang.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace std;
using namespace Iocaste::LikeMagicAdapters;
using namespace irrklang;

namespace Bindings { namespace IrrKlang {

void add_protos(IoVM& vm)
{
    LM_ENUM_PROTOS(vm, (ESM_AUTO_DETECT)(ESM_STREAMING)(ESM_NO_STREAMING)(ESM_FORCE_32_BIT))

    LM_ENUM_PROTOS(vm, (ESOD_AUTO_DETECT)(ESOD_DIRECT_SOUND_8)(ESOD_DIRECT_SOUND)
        (ESOD_WIN_MM)(ESOD_ALSA)(ESOD_CORE_AUDIO)(ESOD_NULL)(ESOD_COUNT)(ESOD_FORCE_32_BIT)
    )

    LM_ENUM_PROTOS(vm, (ESEO_DEFAULT_OPTIONS)(ESEO_MULTI_THREADED)(ESEO_MUTE_IF_NOT_FOCUSED)(ESEO_LOAD_PLUGINS)
        (ESEO_USE_3D_BUFFERS)(ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER)(ESEO_PRINT_DEBUG_INFO_TO_STDOUT)(ESEO_LINEAR_ROLLOFF)
    )

    vm.add_proto("IRR_KLANG_VERSION", IRR_KLANG_VERSION, true);
}

}}

#endif
