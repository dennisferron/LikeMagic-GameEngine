#pragma once

#include "boost/interprocess/offset_ptr.hpp"

namespace LikeMagic { namespace Interprocess {

struct ProcessControlStructure;

struct CallRequest
{
    boost::interprocess::offset_ptr<ProcessControlStructure> sender;
    int invocation_id;
    int object_handle;
    int method_id;
    int args_count;
    char args_buffer[1024];
};

}}
