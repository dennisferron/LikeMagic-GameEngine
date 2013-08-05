// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <irrlicht.h>

#include "LikeMagic/IMarkable.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"

namespace Bindings { namespace Irrlicht {

using Iocaste::LikeMagicAdapters::IoBlock;
using namespace irr;

class ScriptedEventReceiver : public irr::IEventReceiver, public LikeMagic::IMarkable
{
private:
    bool KeyStates[KEY_KEY_CODES_COUNT];

    IoBlock on_OnEvent;

public:

    virtual void mark() const;

    ScriptedEventReceiver(IoBlock onEvent_);

    void setOnEvent(IoBlock block);
    virtual bool OnEvent(SEvent const& event);

    bool isKeyDown(EKEY_CODE keyCode);
};

}}
