#include "Iocaste/MapIntToIoObject.hpp"
#include "IoObject.h"

using namespace Iocaste;

IoObject* MapIntToIoObject::at(int key) const
{
    auto result = keyvalues.find(key);

    if (result == keyvalues.end())
        return nullptr;
    else
        return result->second;
}

IoObject* MapIntToIoObject::atPut(int key, IoObject* value)
{
    return keyvalues[key] = value;
}

void MapIntToIoObject::removeAt(int key)
{
    keyvalues.erase(key);
}
