#pragma once

#include <typeinfo>

namespace LikeMagic { namespace SFMO {

class AbstractObjectSet
{
public:
    virtual ~AbstractObjectSet() {}
    virtual void reset() = 0;
    virtual bool at_end() const = 0;
    virtual void advance() = 0;
    virtual std::string obj_type_descr() = 0;
};

}}
