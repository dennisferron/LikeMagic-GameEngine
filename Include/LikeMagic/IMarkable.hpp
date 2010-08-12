// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include <stdexcept>

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

    // Overloads to mark actually markable things.
    static void markIfMarkable(IMarkable const* ptr) { ptr->mark(); }
    static void markIfMarkable(IMarkable const& ref) { ref.mark(); }

    // This overload catches things that are not markable.
    template <typename T> static void markIfMarkable(T const&) {}
};

}
