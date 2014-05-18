#pragma once

#include "LikeMagic/Utility/DLLHelper.hpp"

#include <stdexcept>

namespace LM {

class DbException : public std::exception
{
};

class TraceDb
{
public:
    virtual void open(std::string program_name) = 0;
    virtual void close() = 0;
    virtual void test() = 0;
};

LIKEMAGIC_API extern TraceDb* trace_db;

}
