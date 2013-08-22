#pragma once

namespace LM {

struct CallReturn
{
    int invocation_id;
    char rvalue_buffer[512];
};

}
