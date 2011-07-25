// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"

#ifndef USE_IRRKLANG

// Define the irrklang bindings as a dummy function.
using namespace LikeMagic;
namespace Bindings { namespace IrrKlang {
void add_bindings(Namespace const& type_sys) {}
}}

#else

#include "irrKlang.h"

using namespace LikeMagic;
using namespace irrklang;

namespace Bindings { namespace IrrKlang {

void add_bindings(Namespace const& type_sys)
{
    LM_STATIC_FUNC(type_sys, irrklang, createIrrKlangDevice)

    LM_CLASS(type_sys, ISound)

    LM_CLASS(type_sys, ISoundEngine)
    LM_FUNC(ISoundEngine, (drop))

    LM_FUNC_OVERLOAD(ISoundEngine, "play2D", play2D,
        ISound*,
        ISoundSource*,
        bool,
        bool,
        bool,
        bool
    )

    LM_FUNC_OVERLOAD(ISoundEngine, "play2D", play2D,
        ISound*,
        const char*,
        bool,
        bool,
        bool,
        E_STREAM_MODE,
        bool
    )

    LM_CLASS(type_sys, E_SOUND_ENGINE_OPTIONS)
    type_sys.add_conv<E_SOUND_ENGINE_OPTIONS, int>();

    LM_CLASS(type_sys, E_SOUND_OUTPUT_DRIVER)
    type_sys.add_conv<E_SOUND_OUTPUT_DRIVER, int>();

    LM_CLASS(type_sys, E_STREAM_MODE)
}

}}

#endif
