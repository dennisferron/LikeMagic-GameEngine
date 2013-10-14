// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/IrrKlang/IrrKlangValues.hpp"

#ifndef USE_IRRKLANG

// Replace protos with empty dummy function.
using namespace LM;
namespace Bindings { namespace IrrKlang {
IRRKLANG_BINDINGS_API void add_values() {}
}}

#else

#include "irrKlang.h"

#include "LikeMagic/BindingMacros.hpp"

using namespace std;
using namespace Iocaste::LMAdapters;
using namespace irrklang;

namespace Bindings { namespace IrrKlang {

IRRKLANG_BINDINGS_API void add_values()
{
    auto& ns = type_system->global_namespace();

    LM_ENUM_VALUES(ns, (ESM_AUTO_DETECT)(ESM_STREAMING)(ESM_NO_STREAMING)(ESM_FORCE_32_BIT))

    LM_ENUM_VALUES(ns, (ESOD_AUTO_DETECT)(ESOD_DIRECT_SOUND_8)(ESOD_DIRECT_SOUND)
        (ESOD_WIN_MM)(ESOD_ALSA)(ESOD_CORE_AUDIO)(ESOD_NULL)(ESOD_COUNT)(ESOD_FORCE_32_BIT)
    )

    LM_ENUM_VALUES(ns, (ESEO_DEFAULT_OPTIONS)(ESEO_MULTI_THREADED)(ESEO_MUTE_IF_NOT_FOCUSED)(ESEO_LOAD_PLUGINS)
        (ESEO_USE_3D_BUFFERS)(ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER)(ESEO_PRINT_DEBUG_INFO_TO_STDOUT)(ESEO_LINEAR_ROLLOFF)
    )

    LM_ADD_VALUE(ns, "IRR_KLANG_VERSION", IRR_KLANG_VERSION);
}

}}

#endif
