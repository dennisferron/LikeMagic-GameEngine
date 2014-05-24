#pragma once

#include "LikeMagic/Utility/DLLHelper.hpp"
#include "LikeMagic/Utility/TypeIndex.hpp"

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
    virtual void register_type_index(TypeIndex type) = 0;
    virtual void new_Expr(void const* addr, TypeIndex type, void const* value_ptr) = 0;
};

LIKEMAGIC_API extern TraceDb* trace_db;

}
