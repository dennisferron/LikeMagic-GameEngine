#pragma once

#include "LikeMagic/Utility/DLLHelper.hpp"

namespace LM {

class TraceDb
{
public:
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void test() = 0;
};

LIKEMAGIC_API extern TraceDb* trace_db;

}
