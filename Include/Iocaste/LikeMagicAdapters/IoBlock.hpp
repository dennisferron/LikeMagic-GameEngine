// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Iocaste/LikeMagicAdapters/API_Io.hpp"

#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/SFMO/ExprProxy.hpp"
#include "LikeMagic/SFMO/Term.hpp"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/DebugInfo.hpp"

#include "Iocaste/Exception.hpp"

#include <tuple>

namespace Iocaste { namespace LikeMagicAdapters {

using LikeMagic::AbstractTypeSystem;
using namespace LikeMagic::SFMO;

class IoVM;

class IoBlock : public LikeMagic::IMarkable, public LikeMagic::DebugInfo
{
private:
    AbstractTypeSystem const* type_sys;
    IoVM* iovm;
    friend class IoVM;

    // The block to activate
    IoObject* io_block;

    // The target on which to activate the block.
    IoObject* io_target;

    template <typename T>
    AbstractCppObjProxy* make_proxy(T t) const
    {
        return ExprProxy::create(Term<T, true>::create(t), *type_sys);
    }

    void add_arg(IoMessage* m, AbstractCppObjProxy* proxy) const;

    void add_args(IoMessage* m) const {}

    template <typename Arg0, typename... Args>
    void add_args(IoMessage* m, Arg0 arg0, Args... args) const
    {
        add_arg(m, make_proxy(arg0));
        add_args(m, args...);
    }

    IoObject* activate(IoMessage* m) const;

public:
    IoBlock();
    IoBlock(AbstractTypeSystem const* type_sys_, IoVM* iovm_, IoObject* io_block_, IoObject* io_target_);
    IoBlock(IoBlock const& other);
    virtual ~IoBlock();

    IoBlock& operator =(IoBlock const& other);

    template <typename... Args>
    void operator()(Args... args) const
    {
        if (type_sys && io_block && io_target)
        {
            IoMessage* m = new_message(io_target, "IoBlock");
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
                m = new_message(io_target, "IoBlock");
                errorPoint = "while adding args";
                add_args(m, args...);
                errorPoint = "on activate";
                IoObject* result = activate(m);
                static TypeIndex r_type = LikeMagic::Utility::BetterTypeInfo::template create_index<R>();
                errorPoint = "return value from_script";
                ExprPtr expr = from_script(io_target, result, *type_sys, r_type);
                errorPoint = "try_conv return value";
                return type_sys->try_conv<R>(expr)->eval();
            }
            catch (Iocaste::ScriptException const& exc)
            {
                // TODO:  assoc addn'l info w/exp.
                throw;
            }
            // TODO:  Create LikeMagic exception object.
            catch (std::exception const& e)
            {
                throw Iocaste::IoStateError(io_block, std::string() + "Error in IoBlock " + errorPoint + ": " + e.what(), m);
            }
        }
        else
        {
            throw std::logic_error("Tried to eval an empty block.");
        }
    }

    bool empty() const;

    virtual void mark() const;
};


}}
