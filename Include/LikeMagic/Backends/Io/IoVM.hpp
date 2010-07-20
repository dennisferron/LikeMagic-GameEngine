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

namespace LikeMagic { namespace Backends { namespace Io {

class IoVM
{
private:
    AbstractTypeSystem& type_system;
    IoState* self;

    ExprPtr get_abs_expr(std::string io_code) const;

public:
    IoVM(AbstractTypeSystem& type_system_);
    ~IoVM();

    void add_proto(std::string name, AbstractCppObjProxy* proxy, bool to_script=false) const;

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
