#pragma once

#include "LikeMagic/Utility/TypeIndex.hpp"
#include "boost/unordered_map.hpp"

#include <vector>

extern "C"
{
    struct CollectorMarker;
    typedef CollectorMarker IoObject;
}

namespace Iocaste {

using LM::TypeIndex;

class Primitives
{
private:

    boost::unordered_map<TypeIndex, IoObject*> protos;

public:

    Primitives();
    ~Primitives();
    void add(TypeIndex index, IoObject* proto);
    IoObject* get(TypeIndex index) const;
    TypeIndex indexOf(std::string name) const;
    std::vector<IoObject*> toList() const;
};

}
