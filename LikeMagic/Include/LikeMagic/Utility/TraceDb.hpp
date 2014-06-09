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
    virtual void register_type_index(TypeIndex type) = 0;
    virtual void new_Expr(void const* addr, TypeIndex type, void const* value_ptr) = 0;
    virtual void new_IoTag(void const* addr, std::string name) = 0;
    virtual void new_IoObject(void const* addr, void const* proto, char const* proto_name, void const* io_tag) = 0;
    virtual void update_IoObject_data(void const* addr, void const* data) = 0;
    virtual void new_IoMessage(void const* addr) = 0;
    virtual void update_IoMessage_name(void const* addr, char const* name) = 0;
    virtual void update_IoMessage_label(void const* addr, char const* label) = 0;
    virtual void update_IoMessage_line(void const* addr, int line) = 0;
    virtual void update_IoMessage_character(void const* addr, int character) = 0;
    virtual void new_IoCall(void const* addr) = 0;
    virtual void update_IoCall_message(void const* addr, void const* message) = 0;
    virtual void IoStack_push_object(void const* object) = 0;
    virtual void IoStack_set_mark(size_t mark) = 0;
    virtual void IoStack_pop_mark(size_t mark) = 0;
    virtual void delete_Expr(void const* addr) = 0;
    virtual void delete_IoObject(void const* addr) = 0;
    virtual void delete_IoMessage(void const* addr) = 0;
    virtual void delete_IoCall(void const* addr) = 0;
    virtual void delete_IoTag(void const* addr) = 0;
};

LIKEMAGIC_API extern TraceDb* trace_db;

}

#define NO_USE_TRACE_DB

#ifdef USE_TRACE_DB
#define IF_TRACE_DB(code) code
#else
#define IF_TRACE_DB(code)
#endif
