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

typedef void* LangObjPtr;

class LangInterpreter : public MarkableObjGraph
{
public:
    virtual ~LangInterpreter() = 0;
    virtual void add_value(std::string name, ExprPtr expr,
                           std::string ns = "", bool conv_to_script=false) = 0;

    virtual LangObjPtr do_string(std::string code) = 0;
    virtual LangObjPtr CastToLangObject(void* object) = 0;
    virtual ExprPtr eval(std::string io_code) = 0;
    virtual void mark() const = 0;

    template <typename T>
    T get_expr(LangInterpreter& interpreter, std::string script_code)
    {
        ExprPtr expr = eval(script_code);
        ExprPtr warden;
        return EvalAs<T>::value(expr, warden);
    }

    // This is intended for pointers but I used "T" instead of "T*" so that you can specify a smart pointer instead.
    template <typename T>
    T get_resource(std::string script_code)
    {
        ExprPtr ptr = get_expr<T>(script_code);

        if (ptr == NULL)
            throw std::logic_error("Failed to get resource object '" + script_code + "'");

        return ptr;
    }

    template <typename T>
    void add_value(std::string name,  T obj=T(), std::string ns = "", bool to_script=false)
    {
        add_value
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
};
}
