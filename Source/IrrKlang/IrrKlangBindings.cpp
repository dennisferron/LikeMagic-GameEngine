// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"
#include "LikeMagic/BindingMacros.hpp"

#ifndef USE_IRRKLANG

// Define the irrklang bindings as a dummy function.
using namespace LikeMagic;
namespace Bindings { namespace IrrKlang {
void add_bindings() {}
}}

#else

#include "irrKlang.h"

using namespace LikeMagic;
using namespace irrklang;

namespace Bindings { namespace IrrKlang {

void add_bindings(Namespace const& type_sys)
{
    LM_STATIC_FUNC(irrklang, createIrrKlangDevice)

    LM_CLASS(ISound)

    LM_CLASS(ISoundEngine)
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

    LM_CLASS(E_SOUND_ENGINE_OPTIONS)
    type_system->add_conv<E_SOUND_ENGINE_OPTIONS, int>();

    LM_CLASS(E_SOUND_OUTPUT_DRIVER)
    type_system->add_conv<E_SOUND_OUTPUT_DRIVER, int>();

    LM_CLASS(E_STREAM_MODE)
}

}}

#endif
