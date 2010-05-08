#pragma once

#include "ConvertibleTo.hpp"
#include "LikeMagic/SFMO/Trampoline.hpp"
#include "LikeMagic/SFMO/StringCachingTrampoline.hpp"

#include "boost/type_traits.hpp"

#include <string>
#include <algorithm>

namespace LikeMagic { namespace TypeConv {

using namespace LikeMagic::SFMO;

template <typename T> struct IsString { enum { value = false }; };

template <> struct IsString<std::string> { enum { value = true }; };
template <> struct IsString<std::string&> { enum { value = true }; };

template <> struct IsString<std::wstring> { enum { value = true }; };
template <> struct IsString<std::wstring&> { enum { value = true }; };

template <> struct IsString<wchar_t *> { enum { value = true }; };
template <> struct IsString<wchar_t *&> { enum { value = true }; };
template <> struct IsString<wchar_t const *> { enum { value = true }; };
template <> struct IsString<wchar_t const *&> { enum { value = true }; };

// A lot of the references in these conv impls should be converted to const-reference just because they are not
// modified, and then other changes should be made to use the const& version of most things.  Even value type
// stuff could accept the source string by const reference.


template <typename F, typename T> struct StringConvImpl
{
    static_assert(false && sizeof(T), "Invalid string conversion impl");
    
    inline static T do_conv(F obj)
    {
        throw std::logic_error("Error, StringConvImpl:  cannot do string conversion from type "
                + BetterTypeInfo::create<F>().describe()
                + " to type "
                + BetterTypeInfo::create<T>().describe());
    }
};

// This is OK - returns a copy of the string.
template <> struct StringConvImpl<std::string&, std::string>
{
    inline static std::string do_conv(std::string& str)
    {
        return str;
    }
};

// This conversion is OK - the strings passed by value are copied.
template <> struct StringConvImpl<std::string, std::wstring>
{
    inline static std::wstring do_conv(std::string str)
    {
        return std::wstring(str.begin(), str.end());
    }
};

// This conversion is OK - the strings passed by value are copied.
template <> struct StringConvImpl<std::string&, std::wstring>
{
    inline static std::wstring do_conv(std::string& str)
    {
        return std::wstring(str.begin(), str.end());
    }
};

// It is not OK to use this conversion.  You can't do a double conversion
// without an intermediate cache.  It has to be handled by class StringConv.
template <> struct StringConvImpl<std::string, wchar_t const*>
{
    /* This cannot be allowed - what we must actually do is
     * convert the string to a wstring, cache it, and then
     * convert that to a wchar_t const*.
    inline static wchar_t const* do_conv(std::string str)
    {
        return StringConvImpl<std::string, std::wstring>::do_conv(str).c_str();
    }
     */
};

// It is not OK to use this conversion.  You can't do a double conversion
// without an intermediate cache.  It has to be handled by class StringConv.
template <> struct StringConvImpl<std::string&, wchar_t const*>
{
    /* This cannot be allowed - what we must actually do is
     * convert the string to a wstring, cache it, and then
     * convert that to a wchar_t const*.
    inline static wchar_t const* do_conv(std::string& str)
    {
        return StringConvImpl<std::string, std::wstring>::do_conv(str).c_str();
    }
    */
};

// This is OK because the char const* refers directly to the string's
// bytes which are (presumed) somewhat permanent as it is a reference.
template <> struct StringConvImpl<std::string&, char const*>
{
    inline static char const* do_conv(std::string const& str)
    {
        return str.c_str();
    }
};

// This is OK because the wchar_t const* refers directly to the string's
// bytes which are (presumed) somewhat permanent as it is a reference.
template <> struct StringConvImpl<std::wstring&, wchar_t const*>
{
    inline static wchar_t const* do_conv(std::wstring const& str)
    {
        return str.c_str();
    }
};

// This is OK because the output is passed by copying.
template <> struct StringConvImpl<std::wstring, std::string>
{
    inline static std::string do_conv(std::wstring str)
    {
        return std::string(str.begin(), str.end());
    }
};

// This is OK because the output is passed as a copy.
template <> struct StringConvImpl<std::wstring&, std::string>
{
    inline static std::string do_conv(std::wstring& str)
    {
        return StringConvImpl<std::wstring, std::string>::do_conv(str);
    }
};

// This is ok because the bytes are copied into the string which is passed by value.
template <> struct StringConvImpl<wchar_t const*, std::string>
{
    inline static std::string do_conv(wchar_t const* str)
    {
        return StringConvImpl<std::wstring, std::string>::do_conv(std::wstring(str));
    }
};

// This is OK
template <> struct StringConvImpl<wchar_t const*&, std::string>
{
    inline static std::string do_conv(wchar_t const*& str)
    {
        return StringConvImpl<std::wstring, std::string>::do_conv(std::wstring(str));
    }
};


// This is ok because the bytes are copied into the string which is passed by value.
template <> struct StringConvImpl<char const*, std::string>
{
    inline static std::string do_conv(char const* str)
    {
        return std::string(str);
    }
};

// This is OK
template <> struct StringConvImpl<char const*&, std::string>
{
    inline static std::string do_conv(char const*& str)
    {
        return std::string(str);
    }
};


template <typename From, typename To>
class StringConv : public ConvertibleTo<To>
{
public:
    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        return Trampoline<From, To, StringConvImpl<From, To>>::create(
            boost::intrusive_ptr<Expression<From>>(
                reinterpret_cast<Expression<From>*>(expr.get())));
    }

    virtual std::string describe() const { return describe_converter<From, To>("StringConv")
            + " (inherits from " + ConvertibleTo<To>::describe() + ")"; }
};


// Special case for when the string must be converted to wide character version.
template <>
class StringConv<std::string, wchar_t const*> : public ConvertibleTo<wchar_t const*>
{
public:
    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        // Convert the string to a wstring and cache it before converting to wchar_t const*.
        return Trampoline<std::wstring&, wchar_t const*, StringConvImpl<std::wstring&, wchar_t const*>>::create(
                StringCachingTrampoline<std::string, std::wstring&, StringConvImpl<std::string, std::wstring>>::create(
                    boost::intrusive_ptr<Expression<std::string>>(
                        reinterpret_cast<Expression<std::string>*>(expr.get()))));
    }

    virtual std::string describe() const { return describe_converter<std::string, wchar_t const*>("StringConv")
            + " (inherits from " + ConvertibleTo<wchar_t const*>::describe() + ")"; }
};

// Special case for when the string must be converted to wide character version.
template <>
class StringConv<std::string&, wchar_t const*> : public ConvertibleTo<wchar_t const*>
{
public:
    virtual ExprPtr wrap_expr(ExprPtr expr) const
    {
        // Convert the string to a wstring and cache it before converting to wchar_t const*.
        return Trampoline<std::wstring&, wchar_t const*, StringConvImpl<std::wstring&, wchar_t const*>>::create(
                StringCachingTrampoline<std::string&, std::wstring&, StringConvImpl<std::string&, std::wstring>>::create(
                    boost::intrusive_ptr<Expression<std::string&>>(
                        reinterpret_cast<Expression<std::string&>*>(expr.get()))));
    }

    virtual std::string describe() const { return describe_converter<std::string&, wchar_t const*>("StringConv")
            + " (inherits from " + ConvertibleTo<wchar_t const*>::describe() + ")"; }
};


}}