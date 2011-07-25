// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include <irrlicht.h>

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"

namespace Bindings { namespace Irrlicht {

using LikeMagic::Backends::Io::IoBlock;
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
