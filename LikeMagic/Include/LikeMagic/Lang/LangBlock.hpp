// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"

#include "LikeMagic/IMarkable.hpp"

#include <tuple>

namespace LM {

class LangBlock : public LM::IMarkable
{
public:
    virtual ~LangBlock();
    virtual LangBlock& operator =(LangBlock const& other) = 0;

    template <typename... Args>
    void operator()(Args... args) const
    {
        if (io_block && io_target)
        {
            IoMessage* m = new_message(io_target, "LangBlock");
            add_args(m, args...);
            activate(m);
        }
    }

    template <typename R, typename... Args>
    R eval(Args... args) const
    {
        if (!empty())
        {
            char const* errorPoint = "before eval";
            IoMessage* m;
            try
            {
                m = new_message(io_target, "LangBlock");
                errorPoint = "while adding args";
                add_args(m, args...);
                errorPoint = "on activate";
                IoObject* result = activate(m);
                static TypeIndex r_type = LM::TypId<R>::get();
                errorPoint = "return value from_script";
                ExprPtr expr = from_script(io_target, result, r_type);
                errorPoint = "try_conv return value";
                ExprPtr warden;
                return EvalAs<R>::value(expr, warden);
            }
            catch (Iocaste::ScriptException const& exc)
            {
                // TODO:  assoc addn'l info w/exp.
                throw;
            }
            // TODO:  Create LikeMagic exception object.
            catch (std::exception const& e)
            {
                throw Iocaste::IoStateError(io_block, std::string() + "Error in LangBlock " + errorPoint + ": " + e.what(), m);
            }
        }
        else
        {
            throw std::logic_error("Tried to eval an empty block.");
        }
    }

    virtual bool empty() const = 0;
    virtual void mark() const = 0;
};


}}
