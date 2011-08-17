// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/Bindings.hpp"

#include <irrlicht.h>

#include "LikeMagic/Utility/UserMacros.hpp"

using namespace LikeMagic;
using namespace irr;

namespace Bindings { namespace Irrlicht {

void add_bindings_irr(RuntimeTypeSystem& type_sys)
{
    auto ns_irr = Namespace::global(type_sys).subspace("irr");

    // functions
    auto& funcs_LM = ns_irr.register_functions();
    funcs_LM.bind_method("createDevice", createDevice);

    LM_CLASS(ns_irr, IReferenceCounted)
    //LM_FUNC(IReferenceCounted, (drop)(grab)(getDebugName)(getReferenceCount))

    LM_CLASS(ns_irr, IrrlichtDevice)
    LM_BASE(IrrlichtDevice, IReferenceCounted)
    LM_FUNC(IrrlichtDevice,
            (activateJoysticks)(clearSystemMessages)(closeDevice)(getColorFormat)(getCursorControl)(getEventReceiver)
            (getFileSystem)(getGammaRamp)(getGUIEnvironment)(getLogger)(getOSOperator)(getSceneManager)(getTimer)
            (getType)(getVersion)(getVideoDriver)(getVideoModeList)(isFullscreen)(isWindowActive)(isWindowFocused)
            (isWindowMinimized)(maximizeWindow)(minimizeWindow)(postEventFromUser)(restoreWindow)(run)(setEventReceiver)
            (setGammaRamp)(setInputReceivingSceneManager)(setResizable)(setWindowCaption)(sleep)(yield)
    )
    LM_STATIC_MEMBER_FUNC(IrrlichtDevice, (isDriverSupported))

    LM_CLASS(ns_irr, ITimer)
    LM_FUNC(ITimer, (getRealTime)(getTime)(setTime)(stop)(start)(setSpeed)(getSpeed)(isStopped)(tick))

    LM_CLASS(ns_irr, SKeyMap)
}

}}
