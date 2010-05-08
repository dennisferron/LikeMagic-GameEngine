#pragma once

namespace LikeMagic
{

class IMarkable
{
public:

    // Called to mark script objects so they won't be deleted.
    virtual void mark() const = 0;
};

}