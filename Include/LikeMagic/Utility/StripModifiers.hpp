// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic { namespace Utility {

// Things like boost::remove_pointer get tripped up if it's something like a "reference to pointer".
// And what if you want to convert a "value const &" to just value?  Nesting std::remove_x gets very wordy.
// OTOH this utility recursively strips ALL the modifiers from a type to get down to the bare essentials.
// In the process, it records what it stripped away so that the values can be used by BetterTypeInfo.
// Example usages:
//
//  StripModifiers<some_type>::strip::type  // a typedef; returns the bare type
//  StripModifiers<some_type>::strip::is_const // bool; Is the value, referenced object, or pointed at object const?
//  StripModifiers<some_type>::strip::is_ref // bool; Is it a reference?
//  StripModifiers<some_type>::strip::is_ptr // bool; Is it a pointer?
//  StripModifiers<some_type>::strip::is_const_ptr // bool; Is it a pointer that can't point at anything else?
//
template <typename T, bool is_const_=false, bool is_ref_=false, bool is_ptr_=false>
struct StripModifiers
{
    typedef StripModifiers<T, is_const_, is_ref_, is_ptr_> strip;
    typedef T type;
    enum { is_const = is_const_ }; // when type is pointer, this means the pointed-at object is const; to find if the bits of the pointer are const see is_const_ptr
    enum { is_ref=is_ref_ };
    enum { is_ptr=is_ptr_ };
};

// First, remove the reference modifier.
template <typename      T, bool is_const_, bool is_ref_, bool is_ptr_>
struct StripModifiers<  T&,     is_const_,      is_ref_,      is_ptr_>
{
    static_assert(!is_const_, "should not have matched const yet");
    static_assert(!is_ptr_, "should not have matched pointer yet");

    typedef typename
        StripModifiers< T,      is_const_,      true,         is_ptr_>
            ::strip strip;
};

// Next, check if it is a pointer-that-is_const (which is different from pointer-to-const!)
// We only want to strip off one level of pointer.  If this is a pointer to a pointer,
// (is_ptr_ already true) then this specialization will not match it.
template <typename      T, bool is_const_, bool is_ref_  /* bool is_ptr_, bool is_const_ptr_ */ >
struct StripModifiers<  T*const,is_const_,      is_ref_,         false>
{
    typedef typename
        StripModifiers< T,      is_const_,      is_ref_,         true>
            ::strip strip;
};

// And check if it is just a plain pointer
// We only want to strip off one level of pointer.  If this is a pointer to a pointer,
// (is_ptr_ already true) then this specialization will not match it.
template <typename      T, bool is_const_, bool is_ref_ /* bool is_ptr_, bool is_const_ptr_ */ >
struct StripModifiers<  T*,     is_const_,      is_ref_,          false>
{
    typedef typename
        StripModifiers< T,      is_const_,      is_ref_,           true>
            ::strip strip;
};

// Finally, check if the value, referenced object, or pointed-to object is const.
template <typename      T, bool is_const_, bool is_ref_, bool is_ptr_>
struct StripModifiers<  const T,is_const_,      is_ref_,      is_ptr_>
{
    typedef typename
        StripModifiers< T,      true,           is_ref_,      is_ptr_>
            ::strip strip;
};


// Short-circuit the recursion for common cases:

#define StripImpl(realType, baseType, is_const_, is_ref_, is_ptr_) \
template <> \
struct StripModifiers<realType, false, false, false> \
{ \
    typedef StripModifiers<realType, false, false, false> strip; \
    typedef baseType type; \
    enum { is_const = is_const_ }; \
    enum { is_ref = is_ref_ }; \
    enum { is_ptr = is_ptr_ }; \
};

#define StripConst(baseType) \
StripPtr(baseType, baseType, false) \
StripPtr(baseType const, baseType, true)

#define StripPtr(realType, baseType, is_const) \
StripRef(realType, baseType, is_const, false) \
StripRef(realType*, baseType, is_const, true)

#define StripRef(realType, baseType, is_const, is_ptr) \
StripImpl(realType, baseType, is_const, false, is_ptr) \
StripImpl(realType&, baseType, is_const, true, is_ptr)

#define StripQuickly(type) StripConst(type)

StripQuickly(char)
StripQuickly(int)
StripQuickly(float)
StripQuickly(double)

}}


