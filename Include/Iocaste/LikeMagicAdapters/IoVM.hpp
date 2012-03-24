// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/RuntimeTypeSystem.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"
#include "LikeMagic/SFMO/ExprProxy.hpp"
#include "LikeMagic/ITypeSystemObserver.hpp"
#include "LikeMagic/MarkableObjGraph.hpp"

#include "boost/unordered_map.hpp"
#include "boost/unordered_set.hpp"

extern "C"
{
    typedef void (CollectorFreeFunc)(void *);
}

namespace Iocaste { namespace LikeMagicAdapters {


class IoVM : public LikeMagic::ITypeSystemObserver, public LikeMagic::MarkableObjGraph
{
private:
    LikeMagic::RuntimeTypeSystem& type_system;
    IoState* state;  // It was dangerous when this was named "self" - Io macros referencing self are defined for an IoObject, not an IoState
    std::set<TypeIndex> registered_classes;
    boost::unordered_map<TypeIndex, IoObject*> class_protos;
    CollectorFreeFunc* original_free_func;

    mutable IoObject* last_exception;

    ExprPtr get_abs_expr(std::string io_code) const;

    IoObject* to_script(IoObject *self, IoObject *locals, IoMessage *m, AbstractCppObjProxy* proxy) const;

    friend class IoBlock;

    IoBlock onRegisterMethod;
    IoBlock onRegisterClass;
    IoBlock onRegisterBase;

    IoBlock onAddProto;

    IoObject* LM_Proxy;
    IoObject* LM_Protos;

    IoObject* proxy_to_io_obj(AbstractCppObjProxy* proxy);

public:
    IoVM(LikeMagic::RuntimeTypeSystem& type_system_);
    ~IoVM();

    static IoObject* perform(IoObject *self, IoObject *locals, IoMessage *m);
    static IoObject* forward(IoObject *self, IoObject *locals, IoMessage *m);
    static void io_exception(void* context, IoObject* coroutine);
    static void willFree(IoObject *self);

    void add_proto(std::string name, AbstractCppObjProxy* proxy, LikeMagic::NamespacePath ns=LikeMagic::NamespacePath::global(), bool conv_to_script=false) const;

    template <typename T>
    void add_proto(std::string name,  T obj=T(), LikeMagic::NamespacePath ns=LikeMagic::NamespacePath::global(), bool to_script=false) const
    {
        add_proto
        (
            name,
            ExprProxy::create
            (
                Term<T, true>::create
                (
                    obj
                ),
                type_system
            ),
            ns,
            to_script
        );
    }

    void run_cli() const;
    IoObject* do_string(std::string io_code) const;

    template <typename T>
    boost::intrusive_ptr<Expression<T>> get_expr(std::string io_code) const
    {
        auto abs_expr = get_abs_expr(io_code);
        return type_system.try_conv<T>(abs_expr);
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

    virtual void register_class(LikeMagic::Marshaling::AbstractClass const* class_);
    virtual void register_base(LikeMagic::Marshaling::AbstractClass const* class_, LikeMagic::Marshaling::AbstractClass const* base);
    virtual void register_method(LikeMagic::Marshaling::AbstractClass const* class_, std::string method_name, LikeMagic::CallTargets::AbstractCallTargetSelector* method);

    virtual void mark() const;

    virtual void setShowAllMessages(bool value);
};


}}
