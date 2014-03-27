#pragma once

#include "boost/unordered_map.hpp"

struct IoObject;

namespace Iocaste {

class MapIntToIoObject
{
private:
    boost::unordered_map<int, IoObject*> keyvalues;
public:
    IoObject* at(int key) const;
    IoObject* atPut(int key, IoObject* value);
    void removeAt(int key);
};

}
