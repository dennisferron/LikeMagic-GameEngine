// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/RuntimeTypeSystem.hpp"

#include "LikeMagic/Backends/Io/API_Io.hpp"
#include "LikeMagic/SFMO/CppObjProxy.hpp"
#include "LikeMagic/ITypeSystemObserver.hpp"

#include "boost/unordered_map.hpp"
#include "boost/unordered_set.hpp"

extern "C"
{
    typedef void (CollectorFreeFunc)(void *);
}

namespace LikeMagic { namespace Backends { namespace Io {

class IoVM : public ITypeSystemObserver, public IMarkable
{
private:
    LikeMagic::RuntimeTypeSystem& type_system;
    IoState* state;  // Dangerousfor this to be named "self" - Io macros using self defined for IoObject, not IoState
    std::set<TypeIndex> registered_classes;
    boost::unordered_map<TypeIndex, IoObject*> cpp_protos;
    boost::unordered_map<IoObject*, std::string> watch_for_free;
    boost::unordered_set<IoObject*> freed_objects;
    bool record_freed_flag;
    bool free_watch_flag;
    CollectorFreeFunc* original_free_func;

    mutable IoObject* last_exception;

    ExprPtr get_abs_expr(std::string io_code) const;

    IoObject* to_script(IoObject *self, IoObject *locals, IoMessage *m, AbstractCppObjProxy* proxy) const;

    friend class IoBlock;

    IoObject* create_namespace(LikeMagic::NamespacePtr ns);
    std::string code_to_get_class_proto(LikeMagic::Marshaling::AbstractClass const* class_);

public:
    IoVM(LikeMagic::RuntimeTypeSystem& type_system_);
    ~IoVM();

    void on_collector_free(IoObject* io_obj);

    bool record_freed_objects() const;
    void set_record_freed_objects(bool value);
    bool watch_freed_objects() const;
    void set_watch_freed_objects(bool value);
    void add_watch_for_freed_object(IoObject* io_obj, std::string message);
    bool check_if_freed(IoObject* io_obj);

    static IoObject* io_userfunc(IoObject *self, IoObject *locals, IoMessage *m);
    static void io_exception(void* context, IoObject* coroutine);

    void add_proto(std::string name, AbstractCppObjProxy* proxy, bool conv_to_script=false) const;

    template <typename T>
    void add_proto(std::string name,  T obj=T(), bool to_script=false) const
    {
        add_proto
        (
            name,
            CppObjProxy<T&, true>::create
            (
                Term<T, true>::create
                (
                    obj
                ),
                type_system
            ),
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

    virtual void register_class(LikeMagic::Utility::TypeIndex type_index, LikeMagic::Marshaling::AbstractClass const* class_);
    virtual void register_base(LikeMagic::Marshaling::AbstractClass const* class_, LikeMagic::Marshaling::AbstractClass const* base);
    virtual void register_method(LikeMagic::Marshaling::AbstractClass const* class_, std::string method_name, LikeMagic::Marshaling::AbstractCallTargetSelector* method);

    virtual void mark() const;
};


}}}
