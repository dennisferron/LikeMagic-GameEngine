#pragma once

namespace LikeMagic { namespace Utility {

// Detects if type is legal to use as qualifier for member function pointer.
template<typename T>
class ICanHasMemberFunc
{
private:
    typedef char Yes;
    typedef struct { char a[2]; } No;
    template<typename U> static Yes test(void (U::*f)());
    template<typename U> static No test(...);
public:
    enum { value = sizeof(test<T>(0)) == sizeof(Yes) };
};

}}