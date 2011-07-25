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
using namespace irr::gui;

/*
// For some reason Io is not converting EEVENT_TYPE to integer codes, so the objects weren't comparing equal.
// I've created a non-member operator == overload to take care of that (the operator will be called in Io).
bool op_equals(EEVENT_TYPE const& a, EEVENT_TYPE const& b)
{
    std::cout << "op_equals: " << (a == b) << std::endl;
    return a == b;
}
bool op_notequals(EEVENT_TYPE const& a, EEVENT_TYPE const& b)
{
    std::cout << "op_notequals: " << (a != b) << std::endl;
    return a != b;
}
*/

bool enum_equals(int a, int b)
{
    std::cout << "op_equals: " << (a == b) << std::endl;
    return a == b;
}
bool enum_notequals(int a, int b)
{
    std::cout << "op_notequals: " << (a != b) << std::endl;
    return a != b;
}


namespace Bindings { namespace Irrlicht {

void add_bindings_gui(RuntimeTypeSystem& type_sys)
{
    auto ns_irr_gui = Namespace::global(type_sys).subspace("irr").subspace("gui");

    LM_CLASS(ns_irr_gui, IReferenceCounted)

    LM_CLASS(ns_irr_gui, IGUIEnvironment)
    LM_BASE(IGUIEnvironment, IReferenceCounted)
    LM_FUNC(IGUIEnvironment, (getBuiltInFont)
    )

    LM_CLASS(ns_irr_gui, IGUIFont)
    LM_BASE(IGUIFont, IReferenceCounted)
    LM_FUNC(IGUIFont, (draw)(getDimension)(getKerningHeight)(getKerningWidth)(setKerningHeight)(setKerningWidth)
    )

    LM_ENUM(ns_irr_gui, EKEY_CODE)
    LM_ENUM(ns_irr_gui, EEVENT_TYPE)
    LM_ENUM(ns_irr_gui, EMOUSE_INPUT_EVENT)
    LM_ENUM(ns_irr_gui, E_MOUSE_BUTTON_STATE_MASK)
    LM_ENUM(ns_irr_gui, EGUI_EVENT_TYPE)

    LM_CLASS(ns_irr_gui, SEvent)
    LM_FIELD(SEvent, (EventType)(GUIEvent)(MouseInput)(KeyInput)(JoystickEvent)(LogEvent)(UserEvent))

    typedef SEvent::SGUIEvent SGUIEvent;
    LM_CLASS(ns_irr_gui, SGUIEvent)

    typedef SEvent::SMouseInput SMouseInput;
    LM_CLASS(ns_irr_gui, SMouseInput)
    LM_FIELD(SMouseInput, (Event)(X)(Y)(Wheel)(ButtonStates))
    LM_BIT_FIELD(SMouseInput, Shift)
    LM_BIT_FIELD(SMouseInput, Control)
    LM_FUNC(SMouseInput, (isLeftPressed)(isRightPressed)(isMiddlePressed))

    typedef SEvent::SKeyInput SKeyInput;
    LM_CLASS(ns_irr_gui, SKeyInput)
    LM_FIELD(SKeyInput, (Char)(Key))
    LM_BIT_FIELD(SKeyInput, PressedDown)
    LM_BIT_FIELD(SKeyInput, Shift)
    LM_BIT_FIELD(SKeyInput, Control)

    typedef SEvent::SJoystickEvent SJoystickEvent;
    LM_CLASS(ns_irr_gui, SJoystickEvent)

    typedef SEvent::SLogEvent SLogEvent;
    LM_CLASS(ns_irr_gui, SLogEvent)

    typedef SEvent::SUserEvent SUserEvent;
    LM_CLASS(ns_irr_gui, SUserEvent)
}


}}
