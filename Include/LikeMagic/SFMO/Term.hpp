// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/Expression.hpp"

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/StripModifiers.hpp"
#include "LikeMagic/Utility/TypePack.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_base_of.hpp"

#include <iostream>

namespace LikeMagic { namespace SFMO {

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

// For Debugging.
template <> struct TermStoreAs<bool&> { typedef bool type; };


template <typename T, bool IsCopyable>
class Term :
    public Expression<T&>
{
private:
    char debug_padding[13];

    typename TermStoreAs<T>::type value;

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

    Term() : value()
    {
    }

    template <typename... Args>
    Term(Args && ... args) : value(std::forward<Args>(args)...)
    {
    }

    template <typename... Args>
    Term(Args const& ... args) : value(args...)
    {
    }

public:

    static boost::intrusive_ptr<Expression<T&>> create()
    {
        boost::intrusive_ptr<Expression<T&>> result = new Term();
        return result;
    }

    template <typename... Args>
    static boost::intrusive_ptr<Expression<T&>> create(Args && ... args)
    {
        boost::intrusive_ptr<Expression<T&>> result = new Term(std::forward<Args>(args)...);
        return result;
    }

    template <typename... Args>
    static boost::intrusive_ptr<Expression<T&>> create(Args const& ... args)
    {
        boost::intrusive_ptr<Expression<T&>> result = new Term(args...);
        return result;
    }

    inline virtual T& eval()
    {
        return value;
    }

    virtual boost::intrusive_ptr<Expression<T&>> clone() const { return new Term<T, IsCopyable>(value); }

    virtual std::set<AbstractObjectSet*> get_objsets() const { return std::set<AbstractObjectSet*>(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("Term<" + LikeMagic::Utility::TypeDescr<T>::text() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<typename boost::remove_reference<T>::type>());
    }

};


template <typename T>
class Term<T, false> :
    public Expression<T&>
{
private:
    char debug_padding[13];

    T value;

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

    Term() : value()
    {
    }

    template <typename... Args>
    Term(Args && ... args) : value(std::forward<Args>(args)...)
    {
    }

    template <typename... Args>
    Term(Args const& ... args) : value(args...)
    {
    }

public:

    static boost::intrusive_ptr<Expression<T&>> create()
    {
        boost::intrusive_ptr<Expression<T&>> result = new Term();
        return result;
    }

    template <typename... Args>
    static boost::intrusive_ptr<Expression<T&>> create(Args && ... args)
    {
        boost::intrusive_ptr<Expression<T&>> result = new Term(std::forward<Args>(args)...);
        return result;
    }

    template <typename... Args>
    static boost::intrusive_ptr<Expression<T&>> create(Args const& ... args)
    {
        boost::intrusive_ptr<Expression<T&>> result = new Term(args...);
        return result;
    }

    inline virtual T& eval()
    {
        return value;
    }

    virtual boost::intrusive_ptr<Expression<T&>> clone() const
    {
        throw std::logic_error("Cannot clone " + description() + " because the class is registered as not having a copy constructor.");
    }

    virtual std::set<AbstractObjectSet*> get_objsets() const { return std::set<AbstractObjectSet*>(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("Term<" + LikeMagic::Utility::TypeDescr<T>::text() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<typename boost::remove_reference<T>::type>());
    }

};



template <typename T>
class Term<T*, true> :
    public Expression<T*&>
{
private:
    char debug_padding[13];

    T* value;

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

    Term() : value(NULL)
    {
    }

    Term(T* ptr) : value(ptr)
    {
    }

public:

    static boost::intrusive_ptr<Expression<T*&>> create()
    {
        boost::intrusive_ptr<Expression<T*&>> result = new Term();
        return result;
    }

    static boost::intrusive_ptr<Expression<T*&>> create(T* ptr)
    {
        boost::intrusive_ptr<Expression<T*&>> result = new Term(ptr);
        return result;
    }

    inline virtual T*& eval()
    {
        return value;
    }

    virtual boost::intrusive_ptr<Expression<T*&>> clone() const { return new Term<T*, true>(value); }

    virtual std::set<AbstractObjectSet*> get_objsets() const { return std::set<AbstractObjectSet*>(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("Term<" + LikeMagic::Utility::TypeDescr<T*>::text() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<T>());
    }

    virtual bool is_null() const { return value == NULL; }

};

template <typename T>
class Term<T*, false> :
    public Expression<T*&>
{
private:
    char debug_padding[13];

    T* value;

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

    Term() : value(NULL)
    {
    }

    Term(T* ptr) : value(ptr)
    {
    }

public:

    static boost::intrusive_ptr<Expression<T*&>> create()
    {
        boost::intrusive_ptr<Expression<T*&>> result = new Term();
        return result;
    }

    static boost::intrusive_ptr<Expression<T*&>> create(T* ptr)
    {
        boost::intrusive_ptr<Expression<T*&>> result = new Term(ptr);
        return result;
    }

    inline virtual T*& eval()
    {
        return value;
    }

    virtual boost::intrusive_ptr<Expression<T*&>> clone() const { return new Term<T*, false>(value); }

    virtual std::set<AbstractObjectSet*> get_objsets() const { return std::set<AbstractObjectSet*>(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("Term<" + LikeMagic::Utility::TypeDescr<T*>::text() + ">");
    }

    virtual void mark() const
    {
        mark_if_possible(TypePack<T>());
    }

    virtual bool is_null() const { return value == NULL; }
};


template <bool IsCopyable>
class Term<void, IsCopyable> : public Expression<void>
{
private:
    Term()
    {
        //std::cout << "warning:  void term exists." << std::endl;
    }

public:
    //static boost::intrusive_ptr<Expression<void>> create() { return new Term(); }

    template <typename... Args>
    static boost::intrusive_ptr<Expression<void>> create(Args... args) { return new Term(); }

    // A term never has any object sets, even if it's a container, because it represents one object by itself so it doesn't
    // have anything to iterate against.  There is another class called ContainerSet that holds a Term
    // but represents an element from the set in the held Term; it's target does change when the set is iterated.
    virtual std::set<AbstractObjectSet*> get_objsets() const { return std::set<AbstractObjectSet*>(); }

    inline virtual void eval() { }
    virtual boost::intrusive_ptr<Expression<void>> clone() const { return new Term(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("Term<void>");
    }

    virtual void mark() const { /* can't mark void */ }

};





}}
