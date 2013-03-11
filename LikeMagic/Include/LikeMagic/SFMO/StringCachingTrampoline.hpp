// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Expression.hpp"
#include "LikeMagic/Utility/StripModifiers.hpp"

#include <iostream>

namespace LikeMagic { namespace SFMO {

using namespace LikeMagic::Utility;

// When converting strings to char* or references, the conversion is unsafe in SFMO expressions if a new string has to be generated
// unless this temporary string is stored away somewhere for the pointer to have
// something durable to refer to while the SFMO expression exists.
// This class should probably not be used for other kind of casts.
template <typename From, typename To, typename Converter>
class StringCachingTrampoline : public Expression<To>
{
private:
    typedef typename boost::remove_const<typename boost::remove_reference<To>::type>::type CacheType;

    boost::intrusive_ptr<Expression<From>> from_expr;
    CacheType cached_String;
    std::string test_String;

    StringCachingTrampoline(boost::intrusive_ptr<Expression<From>> expr) : from_expr(expr) {}

public:

    static boost::intrusive_ptr<Expression<To>> create(ExprPtr expr)
    {
        return new StringCachingTrampoline(reinterpret_cast<Expression<From>*>(expr.get()));
    }

    inline virtual To eval()
    {
        //std::cout << "String conversion from expression: " << from_expr->description() << std::endl;
        //std::cout << "Converting string: " << from_expr->eval();
        cached_String = Converter::do_conv(from_expr->eval());

        //cached_String = L"ASDF";

        // Here we may be returning a reference to the cached value instead of by-value.
        return cached_String;

        //std::cout << "About to set test_String" << std::endl;
        //test_String = "ZXCV";
        //std::cout << "test_String: " << test_String << std::endl;
//        std::cout << "string caching converter: " << LikeMagic::Utility::TypeDescr<decltype(*this)>::text() << std::endl;
//
//        std::wstring* p = new std::wstring(L"ASDF");
//        std::cout << "wstring pointer: " << p << std::endl;
//        std::cout << "buf pointer: " << p->c_str() << std::endl;
//
//        return *p;
    }

    virtual boost::intrusive_ptr<Expression<To>> clone() const { return new StringCachingTrampoline(from_expr); }

    virtual bool is_terminal() const { return false; }

    virtual std::string description() const
    {
        return "converts " + from_expr->description() + " from " + LikeMagic::Utility::TypeDescr<From>::text() + " to " + LikeMagic::Utility::TypeDescr<To>::text();
    }

    virtual void mark() const
    {
        from_expr->mark();
    }

};

}}
