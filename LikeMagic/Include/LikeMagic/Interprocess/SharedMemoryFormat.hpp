#pragma once

#include "LikeMagic/Interprocess/ProcessControlStructure.hpp"

namespace LM {

struct SharedMemoryFormat
{
    SharedMemoryFormat()
        {}

    // TODO:  Use a boost::interprocess allocator instead
    ProcessControlStructure processes[10];
};

}
