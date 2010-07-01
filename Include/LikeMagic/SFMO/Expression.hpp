// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
// 
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "AbstractExpression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include <iostream>


namespace LikeMagic { namespace SFMO {

template <typename T>
class Expression : public AbstractExpression
{
private:
    Expression(Expression<T> const& other);
protected:
    Expression()
    {
        //std::cout << "created expression with T=" << LikeMagic::Utility::TypeDescr<T>::text() << std::endl;
    }
public:
    virtual ~Expression() {}
    virtual T eval() = 0;
    virtual boost::intrusive_ptr<Expression<T>> clone() const = 0;
    typedef T ReturnType;
    virtual BetterTypeInfo get_type() const { return BetterTypeInfo::create<T>(); }

    /*
    virtual void eval_and_serialize(std::vector<char>& buffer)
    {
        T result = eval();
        char const* begin = reinterpret_cast<char const*>(&result);
        char const* end = reinterpret_cast<char const*>(&result) + sizeof(T);
        return buffer.insert(buffer.begin(), begin, end);
    }
    */
};

}}
