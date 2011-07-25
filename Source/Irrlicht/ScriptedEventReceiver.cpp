// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/Irrlicht/ScriptedEventReceiver.hpp"

using namespace Bindings::Irrlicht;
using namespace irr::core;
using namespace irr::video;
using namespace irr::scene;

void ScriptedEventReceiver::mark() const
{
    //std::cout << "ScriptedEventReceiver::mark()" << std::endl;
    on_OnEvent.mark();
}

void ScriptedEventReceiver::setOnEvent(IoBlock block) { on_OnEvent = block; }


ScriptedEventReceiver::ScriptedEventReceiver(IoBlock onEvent_)
    : on_OnEvent(onEvent_)
{
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyStates[i] = false;
}


bool ScriptedEventReceiver::OnEvent(SEvent const& event)
{
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyStates[event.KeyInput.Key] = event.KeyInput.PressedDown;

    if (on_OnEvent.empty())
        return false;
    else
        return on_OnEvent.eval<bool>(event);
}

bool ScriptedEventReceiver::isKeyDown(EKEY_CODE keyCode)
{
    return KeyStates[keyCode];
}
