// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expression.hpp"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/StripModifiers.hpp"
#include "LikeMagic/Utility/TypePack.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_base_of.hpp"

#include <iostream>

namespace LikeMagic { namespace Exprs {

using namespace LikeMagic::Utility;


// The compiler seems to treat numeric temporaries as "extra temporary",
// too aggressively deciding the temporary isn't needed and dropping it off the stack.
// So don't allow a const& to be made to any numeric; just store the value.
template <typename T> struct TermStoreAs { typedef T type; };
template <> struct TermStoreAs<float const&> { typedef float type; };
template <> struct TermStoreAs<double const&> { typedef double type; };
template <> struct TermStoreAs<signed char const&> { typedef signed char type; };
template <> struct TermStoreAs<int const&> { typedef int type; };
template <> struct TermStoreAs<long const&> { typedef long type; };
template <> struct TermStoreAs<long long const&> { typedef long long type; };
template <> struct TermStoreAs<unsigned char const&> { typedef unsigned char type; };
template <> struct TermStoreAs<unsigned int const&> { typedef unsigned int type; };
template <> struct TermStoreAs<unsigned long const&> { typedef unsigned long type; };
template <> struct TermStoreAs<unsigned long long const&> { typedef unsigned long long type; };

// Still necessary?
template <> struct TermStoreAs<bool&> { typedef bool type; };

template <typename T>
struct Deleter
{
    static void delete_if_possible(T const& value) { /* do nothing */ }
};

template <typename T>
struct Deleter<T*>
{
    static void delete_if_possible(T* value) { delete value; }
};

template <>
struct Deleter<void*>
{
    static void delete_if_possible(void* value)
    {
        throw std::logic_error("Cannot auto-delete void*.");
    }
};

template <typename T>
class Term : public Expression<T&>
{
private:

    typename TermStoreAs<T>::type value;
    bool disable_to_script;
    bool auto_delete_ptr;

    static void mark(IMarkable const* obj)
    {
        obj->mark();
    }

    static void mark(IMarkable const& obj)
    {
        obj.mark();
    }

    template <typename MarkType>
    typename boost::enable_if<boost::is_base_of<IMarkable, MarkType>
        >::type mark_if_possible(TypePack<MarkType>) const
    {
        mark(value);
    }

    template <typename MarkType>
    typename boost::disable_if<boost::is_base_of<IMarkable, MarkType>
        >::type mark_if_possible(TypePack<MarkType>) const
    {
    }

    Term() : value(), disable_to_script(false)
    {
    }

    template <typename... Args>
    Term(Args && ... args) : value(std::forward<Args>(args)...), disable_to_script(false)
    {
    }

    template <typename... Args>
    Term(Args const& ... args) : value(args...), disable_to_script(false)
    {
    }

public:

    ~Term()
    {
        if (auto_delete_ptr)
            Deleter<T>::delete_if_possible(value);
    }

    void set_auto_delete_ptr(bool value_)
    {
        auto_delete_ptr = value;
    }

    static boost::intrusive_ptr<Term> create()
    {
        return new Term();
    }

    template <typename... Args>
    static boost::intrusive_ptr<Term> create(Args && ... args)
    {
        return new Term(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static boost::intrusive_ptr<Term> create(Args const& ... args)
    {
        return new Term(args...);
    }

    inline virtual T& eval()
    {
        return value;
    }

    virtual bool is_terminal() const { return true; }
    virtual bool disable_to_script_conv() const { return disable_to_script; }
    virtual void set_disable_to_script(bool value) { disable_to_script = value; }

    virtual std::string description() const
    {
        return std::string("Term<" + LikeMagic::Utility::TypeDescr<T>::text() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<
            typename boost::remove_reference<
                typename boost::remove_pointer<
                    T
                >::type
             >::type>());
    }
};

}}
