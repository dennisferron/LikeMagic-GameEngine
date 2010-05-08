#pragma once

#include <type_traits>

namespace LikeMagic { namespace Utility {

// Detects STL-compatible containers
template<typename T>
class IsContainer {
  private:
    typedef char Yes;
    typedef struct { char a[2]; } No;
    template<typename U> static Yes test(typename U::iterator*);
    template<typename U> static No test(...);
  public:
    enum { value = sizeof(test<typename std::remove_reference<T>::type>(0)) == sizeof(Yes) };
};

}}