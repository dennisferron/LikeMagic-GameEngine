// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <irrlicht.h>

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Lang/LangInterpreter.hpp"
#include "LikeMagic/Lang/LangBlock.hpp"

namespace Bindings { namespace Irrlicht {

using LM::BlockPtr;
using namespace irr;

class ScriptedEventReceiver : public irr::IEventReceiver, public LM::IMarkable
{
private:
    bool KeyStates[KEY_KEY_CODES_COUNT];

    BlockPtr on_OnEvent;

public:

    virtual void mark() const;

    ScriptedEventReceiver(BlockPtr onEvent_);

    void setOnEvent(BlockPtr block);
    virtual bool OnEvent(SEvent const& event);

    bool isKeyDown(EKEY_CODE keyCode);
};

}}
