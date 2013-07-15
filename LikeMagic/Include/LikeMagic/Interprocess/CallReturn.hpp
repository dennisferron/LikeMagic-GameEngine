#pragma once

namespace LikeMagic { namespace Interprocess {

struct CallReturn
{
    int invocation_id;
    char rvalue_buffer[512];
};

}}
