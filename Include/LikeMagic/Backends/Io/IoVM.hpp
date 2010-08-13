// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Backends/Io/API_Io.hpp"
#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "boost/unordered_map.hpp"
#include "boost/unordered_set.hpp"

extern "C"
{
    typedef void (CollectorFreeFunc)(void *);
}

namespace LikeMagic { namespace Backends { namespace Io {

class IoVM
{
private:
    AbstractTypeSystem& type_system;
    IoState* self;  // Has to be named "self" for a lot of the Io macros to work.
    boost::unordered_map<TypeInfoKey, IoObject*> cpp_protos;
    boost::unordered_map<IoObject*, std::string> watch_for_free;
    boost::unordered_set<IoObject*> freed_objects;
    bool disable_free_flag;
    bool record_freed_flag;
    bool free_watch_flag;
    CollectorFreeFunc* original_free_func;

    ExprPtr get_abs_expr(std::string io_code) const;

    IoObject* to_script(IoObject *self, IoObject *locals, IoMessage *m, AbstractCppObjProxy* proxy) const;

    friend class IoBlock;

public:
    IoVM(AbstractTypeSystem& type_system_);
    ~IoVM();

    void on_collector_free(IoObject* io_obj);

    bool free_is_disabled() const;
    void set_disable_free(bool value);
    bool record_freed_objects() const;
    void set_record_freed_objects(bool value);
    bool watch_freed_objects() const;
    void set_watch_freed_objects(bool value);
    void add_watch_for_freed_object(IoObject* io_obj, std::string message);
    bool check_if_freed(IoObject* io_obj);

    static IoObject* io_userfunc(IoObject *self, IoObject *locals, IoMessage *m);

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
        auto abs_expr = get_abs_expr(io_code, BetterTypeInfo::create<T>());
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
};


}}}
