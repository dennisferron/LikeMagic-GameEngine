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

    // IMarkable has no virtual destructor by design.  As it is
    // an interface and might be applied to lightweight objects,
    // I didn't want to force virtual destructors on all users of it.
    // Although the memory cost of the vtable is already paid because of the virtual mark() function,
    // presence of a virtual destructor would force all derived objects to be
    // destructed virtually, which might be an unwanted runtime cost.
};

}
