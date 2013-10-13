// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LM {

namespace Private {

// Have to strip off const twice because in e.g.
// char * const & the pointer is const
// but in
// char const * & the object is const
// and in
// char const * const & both are const
// and these need to be treated distinctly.

template <typename T>
struct StripSecondConst
{
    enum { second_const = false };
    typedef T type;
};

template <typename T>
struct StripSecondConst<T const>
{
    enum { second_const = true };
    typedef T type;
};

template <typename T>
struct StripPtr : public StripSecondConst<T>
{
    enum { is_ptr = false };
};

template <typename T>
struct StripPtr<T*> : public StripSecondConst<T>
{
    enum { is_ptr = true };
};

template <typename T>
struct StripFirstConst : public StripPtr<T>
{
    enum { first_const = false };
};

template <typename T>
struct StripFirstConst<T const> : public StripPtr<T>
{
    enum { first_const = true };
};


template <typename T>
struct StripRef : public StripFirstConst<T>
{
    enum { is_ref = false };
};

template <typename T>
struct StripRef<T&> : public StripFirstConst<T>
{
    enum { is_ref = true };
};

}

// Things like boost::remove_pointer get tripped up if it's something like a "reference to pointer".
// And what if you want to convert a "value const &" to just value?  Nesting std::remove_x gets very wordy.
// OTOH this utility recursively strips ALL the modifiers from a type to get down to the bare essentials.
// In the process, it records what it stripped away so that the values can be used by TypeInfo.
// Example usages:
//
//  StripModifiers<some_type>::type  // a typedef; returns the bare type
//  StripModifiers<some_type>::is_const // bool; Is the value, referenced object, or pointed at object const?
//  StripModifiers<some_type>::is_ref // bool; Is it a reference?
//  StripModifiers<some_type>::is_ptr // bool; Is it a pointer?
//
template <typename T>
struct StripModifiers : public Private::StripRef<T>
{
    enum { obj_is_const = Private::StripRef<T>::second_const || (Private::StripRef<T>::first_const && !Private::StripRef<T>::is_ptr)  };
    enum { ptr_is_const = Private::StripRef<T>::is_ptr && Private::StripRef<T>::first_const };
};


}


