// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace irr { namespace scene { class IMeshBuffer; } }

class btSoftBody;

namespace Bindings { namespace Custom {

class SoftBodyMeshSynchronizer
{
private:
    btSoftBody* softBody;
    irr::scene::IMeshBuffer* meshBuf;

public:
    SoftBodyMeshSynchronizer(btSoftBody* softBody_, irr::scene::IMeshBuffer* meshBuf_);
    ~SoftBodyMeshSynchronizer();

    void sync();
};

}}
