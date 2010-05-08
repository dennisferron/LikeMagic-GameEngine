#pragma once

#include <tuple>
#include <vector>

#include "IndexPack.hpp"
#include "TypePack.hpp"
#include "BetterTypeInfo.hpp"

#include "boost/type_traits/is_same.hpp"

namespace LikeMagic { namespace Utility {


// A dummy type used to indicate that a field is a static class member
// or a global C++ variable that doesn't have an object associated with it.
struct StaticField {};

template <typename F>
struct FieldPtrTraits
{

    // A helper type that wraps up all values of the variable's traits.
    template <bool is_const_, typename R_, typename ObjT_>
    struct Sig
    {
        enum { is_const = is_const_ };

        typedef R_ R;
        typedef ObjT_ ObjT;
    };

    // One of the following test() functions will correspond to the type F:

    // Nonconst member variables.
    template <typename R, typename ObjT>
    static Sig<false, R, ObjT> test(R ObjT::*f);

    // Const member variables.
    template <typename R, typename ObjT>
    static Sig<true, R, ObjT> test(const R ObjT::*f);

    // Static member variables and ordinary (namespace-level) variables.
    template <typename R>
    static Sig<false, R, StaticField> test(R *f);

    // Const static member variables and const ordinary (namespace-level) variables.
    template <typename R>
    static Sig<true, R, StaticField> test(const R *f);


    // for arrays:  we want R to be the type of an array element, not an array itself.

    // Nonconst member variables.
    template <typename R, typename ObjT, int N>
    static Sig<false, R, ObjT> test(R (ObjT::*f)[N]);

    // Const member variables.
    template <typename R, typename ObjT, int N>
    static Sig<true, R, ObjT> test(const R (ObjT::*f)[N]);

    // Static member variables and ordinary (namespace-level) variables.
    template <typename R, int N>
    static Sig<false, R, StaticField> test(R (*f)[N]);

    // Const static member variables and const ordinary (namespace-level) variables.
    template <typename R, int N>
    static Sig<true, R, StaticField> test(const R (*f)[N]);


    // Figure out what result of invoking test() on a pointer of type "F" would be.
    typedef decltype(test(F(0))) Signature;

    // Return value of the function.
    typedef typename Signature::R R;

    // Target object of the function.  "void" if not a nonstatic member function.
    typedef typename Signature::ObjT ObjT;

    enum { is_const = Signature::is_const };
};

}}