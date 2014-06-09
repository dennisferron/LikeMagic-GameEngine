// LikeMagic C++ Binding Library
// Copyright 2008-2014 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/BindingMacros.hpp"

namespace LM {


class CharConstPtrToStringConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        ExprPtr result = Term<std::string>::create(
                reinterpret_cast<char const*>(
                    expr->get_value_ptr().as_const));
        return result;
    }

    virtual std::string description() const { return "CharConstPtrToStringConv"; }
    virtual float cost() const { return 500.0; }
};

class StringToCharConstPtr : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        ExprPtr result = Term<char const*>::create(
                reinterpret_cast<std::string const*>(
                    expr->get_value_ptr().as_const)
                       ->c_str());
        return result;
    }

    virtual std::string description() const { return "StringToCharConstPtr"; }
    virtual float cost() const { return 25.0; }
};

class WCharConstPtrToWStringConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        ExprPtr result = Term<std::wstring>::create(
                reinterpret_cast<wchar_t const*>(
                    expr->get_value_ptr().as_const));
        return result;
    }

    virtual std::string description() const { return "WCharConstPtrToWStringConv"; }
    virtual float cost() const { return 500.0; }
};

class WStringToWCharConstPtr : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        ExprPtr result = Term<wchar_t const*>::create(
                reinterpret_cast<std::wstring const*>(
                    expr->get_value_ptr().as_const)
                       ->c_str());
        return result;
    }

    virtual std::string description() const { return "WStringToWCharConstPtr"; }
    virtual float cost() const { return 25.0; }
};

class StringToWStringConv : public AbstractTypeConverter
{
public:

    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        std::string const* src =
            reinterpret_cast<std::string const*>(
                expr->get_value_ptr().as_const);

        ExprPtr result = Term<std::wstring>::create(std::wstring());

        std::wstring* dst =
            reinterpret_cast<std::wstring*>(
                expr->get_value_ptr().as_nonconst);

        for (char ch : *src)
            *dst += (wchar_t)ch;

        return result;
    }

    virtual std::string description() const { return "StringToWStringConv"; }
    virtual float cost() const { return 500.0; }
};


void add_string_convs()
{
    TypeMirror& global_ns = type_system->global_namespace();
    TypeMirror& ns_std = register_namespace("std", global_ns);

    type_system->add_converter_variations(
        TypId<char const*>::liberal(),
        TypId<std::string>::liberal(),
            new CharConstPtrToStringConv);

    type_system->add_converter_variations(
        TypId<std::string>::liberal(),
        TypId<char const*>::restricted(),
            new StringToCharConstPtr);

    type_system->add_converter_variations(
        TypId<wchar_t const*>::liberal(),
        TypId<std::wstring>::liberal(),
            new WCharConstPtrToWStringConv);

    type_system->add_converter_variations(
        TypId<std::wstring>::liberal(),
        TypId<wchar_t const*>::restricted(),
            new WStringToWCharConstPtr);

    type_system->add_converter_variations(
        TypId<std::string>::liberal(),
        TypId<std::wstring>::liberal(),
            new StringToWStringConv);

    type_system->add_converter_variations(
        TypId<std::string const&>::liberal(),
        TypId<std::wstring>::liberal(),
            new StringToWStringConv);
}


}
