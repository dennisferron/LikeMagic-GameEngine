// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"
#include "LikeMagic/MarkableObjGraph.hpp"

#include "Iocaste/Breakpoint.hpp"
#include "Iocaste/Primitives.hpp"

#include "boost/unordered_map.hpp"
#include "boost/unordered_set.hpp"

#include "IoState.h"

extern "C"
{
    typedef void (CollectorFreeFunc)(void *);
    List* IoState_tagList(IoState *self);
}

namespace Iocaste { namespace LikeMagicAdapters {


class IoVM : public IoState, public LikeMagic::MarkableObjGraph
{
private:
    friend IOVM_API void ::IoState_registerProtoWithId_(IoState *self, IoObject *proto, const char *v);
    friend IOVM_API IoObject* ::IoState_protoWithName_(IoState *self, const char *name);
    friend List* ::IoState_tagList(IoState *self);

    IoState* state;  // It was dangerous when this was named "self" - Io macros referencing self are defined for an IoObject, not an IoState
    Primitives primitives;
    std::set<TypeIndex> registered_classes;
    boost::unordered_map<TypeIndex, IoObject*> class_protos;
    CollectorFreeFunc* original_free_func;
    mutable IoObject* last_exception;
    std::vector<Breakpoint> breakpoints;

    ExprPtr get_abs_expr(std::string io_code) const;

    IoObject* to_script(IoObject *self, IoObject *locals, IoMessage *m, ExprPtr expr) const;

    friend class IoBlock;

    IoBlock onRegisterMethod;
    IoBlock onRegisterClass;
    IoBlock onRegisterBase;

    IoBlock onAddProto;

    IoObject* LM_Proxy;
    IoObject* LM_Protos;

    std::map<std::string, std::string> paths;

    IoObject* expr_to_io_obj(ExprPtr expr);

public:
    IoVM(std::string bootstrap_path);
    ~IoVM();

    static IoObject* perform(IoObject *self, IoObject *locals, IoMessage *m);
    static IoObject* forward(IoObject *self, IoObject *locals, IoMessage *m);
    static void io_exception(void* context, IoObject* coroutine);
    static void willFree(IoObject *self);

    std::string get_path(std::string path_identifier);
    void set_path(std::string path_identifier, std::string path_value);

    void add_proto(std::string name, ExprPtr expr, std::string ns = "", bool conv_to_script=false) const;

    void run_cli() const;
    IoObject* do_string(std::string io_code) const;

    template <typename T>
    boost::intrusive_ptr<Expression<T>> get_expr(std::string io_code) const
    {
        auto abs_expr = get_abs_expr(io_code);
        return try_conv<T>(abs_expr);
    }

    // This is intended for pointers but I used "T" instead of "T*" so that you can specify a smart pointer instead.
    template <typename T>
    T get_resource(std::string io_code) const
    {
        auto ptr = get_expr<T>(io_code)->eval();

        if (ptr == NULL)
            throw std::logic_error("Failed to get resource object '" + io_code + "'");

        return ptr;
    }

    IoObject* castToIoObjectPointer(void* object);

    virtual void register_class(LikeMagic::Mirrors::TypeMirror const* class_);
    virtual void register_base(LikeMagic::Mirrors::TypeMirror const* class_, LikeMagic::Mirrors::TypeMirror const* base);
    virtual void register_method(LikeMagic::Mirrors::TypeMirror const* class_, std::string method_name, LikeMagic::Mirrors::CallTarget* method);

    virtual void mark() const;

    virtual void setShowAllMessages(bool value);

    void set_breakpoint(int breakpoint_number, const char *file_name, int line_number);
    void set_pending_breakpoints(IoMessage* m);
    Breakpoint* find_pending_breakpoint(std::string file_name, int line_number, int char_number);
    Breakpoint* find_pending_breakpoint(IoMessage* m);

    static IoVM* get(IoState* state);
    static IoVM* get(IoMessage* m);
};

template <typename T>
void add_proto(IoVM& iovm, std::string name,  T obj=T(), std::string ns = "", bool to_script=false)
{
    iovm.add_proto
    (
        name,
        Term<T>::create
        (
            obj
        ),
        ns,
        to_script
    );
}

}}
