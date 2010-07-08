// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractObjectSet.hpp"
#include "Expression.hpp"
#include <type_traits>

namespace LikeMagic { namespace SFMO {

template <typename Container>
class ContainerSet : public AbstractObjectSet, public Expression<decltype(*typename Container::iterator())>
{
public:
    typedef decltype(*typename Container::iterator()) ReturnType;

private:
    boost::intrusive_ptr<Expression<Container&>> container_expr;

    typename Container::iterator iter;
    typename Container::iterator end;

    ContainerSet(boost::intrusive_ptr<Expression<Container&>> expr_) : container_expr(expr_) { reset(); }

public:

    static boost::intrusive_ptr<Expression<ReturnType>> create(boost::intrusive_ptr<Expression<Container&>> expr)
        { return new ContainerSet(expr); }

    virtual std::set<AbstractObjectSet*> get_objsets()
    {
        std::set<AbstractObjectSet*> objsets;
        objsets.insert(this);
        return objsets;
    }

    virtual bool is_terminal() const { return false; }
    virtual bool is_lazy() const { return container_expr->is_lazy(); }

    inline virtual ReturnType eval()
    {
        if (iter == end)
            throw std::logic_error("set exhausted; need to reset it before eval elements again");
        else
            return *iter;
    }

    virtual boost::intrusive_ptr<Expression<ReturnType>> clone() const { return new ContainerSet<Container>(container_expr); }

    virtual std::string description() const
    {
        return "element " + LikeMagic::Utility::TypeDescr<ReturnType>::text() + " of " + container_expr->description();
    }

    // AbstractObjectSet functions.
    virtual void reset()
    {
        //std::cout << "reset containerset" << std::endl;
        iter = container_expr->eval().begin();
        end = container_expr->eval().end();
    }

    virtual bool at_end() const { return iter == end; }

    virtual void advance()
    {
        if (iter==end)
            throw std::logic_error("containerset advanced past the end");

        //std::cout << "advancing containerset" << std::endl;
        ++iter;
    }

    virtual std::string obj_type_descr() { return LikeMagic::Utility::TypeDescr<typename Container::value_type>::text(); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() { container_expr->mark(); }

};

}}
