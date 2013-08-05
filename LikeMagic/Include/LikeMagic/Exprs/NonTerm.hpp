// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/SFMO/Term.hpp"

#include <iostream>

namespace LikeMagic { namespace SFMO {

using namespace LikeMagic::Utility;

template <typename T, bool IsCopyable>
class NonTerm :
    public Term<T, IsCopyable>
{
private:
    typename TermStoreAs<T>::type value;

    NonTerm() : Term()
    {
    }

    template <typename... Args>
    NonTerm(Args && ... args) : Term(std::forward<Args>(args)...)
    {
    }

    template <typename... Args>
    NonTerm(Args const& ... args) : Term(args...)
    {
    }

public:

    static boost::intrusive_ptr<Expression<T&>> create()
    {
        boost::intrusive_ptr<Expression<T&>> result = new NonTerm();
        return result;
    }

    template <typename... Args>
    static boost::intrusive_ptr<Expression<T&>> create(Args && ... args)
    {
        boost::intrusive_ptr<Expression<T&>> result = new NonTerm(std::forward<Args>(args)...);
        return result;
    }

    template <typename... Args>
    static boost::intrusive_ptr<Expression<T&>> create(Args const& ... args)
    {
        boost::intrusive_ptr<Expression<T&>> result = new NonTerm(args...);
        return result;
    }

    virtual bool is_terminal() const { return false; }
    virtual bool is_lazy() const { return true; }

    virtual std::string description() const
    {
        return std::string("Reference<" + LikeMagic::Utility::TypeDescr<T>::text() + ">");
    }

    virtual void mark() const
    {
        typedef typename StripModifiers<T>::strip::type MarkType;
        mark_if_possible(TypePack<MarkType>());
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
        typedef typename StripModifiers<T>::strip::type MarkType;
        mark_if_possible(TypePack<MarkType>());
    }

};


template <bool IsCopyable>
class Term<void, IsCopyable> : public Expression<void>
{
private:
    Term()
    {
        std::cout << "warning:  void term exists." << std::endl;
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
