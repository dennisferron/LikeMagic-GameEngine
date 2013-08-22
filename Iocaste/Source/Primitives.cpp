
#include "Iocaste/Primitives.hpp"
#include "Iocaste/LikeMagicAdapters/FromIoTypeInfo.hpp"

#include "IoObject.h"

using namespace Iocaste;
using namespace Iocaste::LMAdapters;

Primitives::Primitives()
{
}

Primitives::~Primitives()
{
    for (auto item : this->toList())
    {
       	//io_free(item->records);
        //io_free(item);
    }
}

void Primitives::add(TypeIndex index, IoObject* proto)
{
    protos[index] = proto;
}

IoObject* Primitives::get(TypeIndex index) const
{
    auto iter = protos.find(index);
    if (iter != protos.end())
        return iter->second;
    else
        return NULL;
}

TypeIndex Primitives::indexOf(std::string name) const
{
    return FromIoTypeInfo::create_index(name);
}

std::vector<IoObject*> Primitives::toList() const
{
    std::vector<IoObject*> result;

    for(auto item : protos)
        result.push_back(item.second);

    return result;
}

