// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Lang/LangBlock.hpp"
#include "LikeMagic/MarkableObjGraph.hpp"

namespace LM {

class LangInterpreter : public MarkableObjGraph
{
public:
    virtual ~LangInterpreter();
    virtual void add_value(std::string name, ExprPtr expr,
                           std::string ns = "", bool conv_to_script=false) const = 0;

    virtual void run_cli() const = 0;
    virtual LangObject* do_string(std::string code) const = 0;

    virtual LangObject* CastToLangObject(void* object) = 0;
    virtual void mark() const = 0;
};

template <typename T>
T get_expr(LangInterpreter& interpreter, std::string io_code) const
{
    auto abs_expr = get_abs_expr(io_code);
    return EvalAs<T>::value(abs_expr);
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

template <typename T>
void add_value(LangInterpreter& interpreter, std::string name,  T obj=T(), std::string ns = "", bool to_script=false)
{
    interpreter.add_value
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

}
