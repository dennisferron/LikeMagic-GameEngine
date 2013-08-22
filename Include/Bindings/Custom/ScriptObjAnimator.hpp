// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "irrlicht.h"
#include "LikeMagic/IMarkable.hpp"

struct CollectorMarker;
typedef CollectorMarker IoObject;

namespace Bindings { namespace Custom {

class ScriptObjAnimator : public irr::scene::ISceneNodeAnimator, public LM::IMarkable
{
public:

    // Irrlicht stuff
    virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
    virtual irr::scene::ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node,
                    irr::scene::ISceneManager* newManager=0);
    irr::scene::ESCENE_NODE_ANIMATOR_TYPE getType() const;

    ScriptObjAnimator(IoObject* io_obj_);

    IoObject* getScriptObj() const;

    static ScriptObjAnimator* findIn(irr::scene::ISceneNode* node);

    virtual void mark() const;

private:

    IoObject* io_obj;
};

}}
