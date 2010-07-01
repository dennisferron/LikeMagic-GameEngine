// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
// 
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LikeMagic { namespace Utility {

// Detects STL container iterators, but not pointers.
template<typename T>
class IsIterator {
  private:
    typedef char Yes;
    typedef struct { char a[2]; } No;
    template<typename U> static Yes test(typename U::iterator_category*);
    template<typename U> static No test(...);
  public:
    enum { value = sizeof(IsIterator<T>::test<T>(0)) == sizeof(Yes) };
};

}}
