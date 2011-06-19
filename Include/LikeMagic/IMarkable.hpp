// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic
{

class IMarkable
{
public:

    // Called to mark script objects so they won't be deleted.
    // The function is const even though an action is taken (marking)
    // because you need to be able to mark even const objects to prevent
    // the GC from collecting script objects it may be pointing too.
    // Declare your script object as a pointer to a "mutable" script object if you have to.
    virtual void mark() const = 0;
};

}
