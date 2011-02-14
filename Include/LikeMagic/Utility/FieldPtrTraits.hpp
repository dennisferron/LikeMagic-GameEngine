// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

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

template <typename F, typename CallAs>
struct FieldPtrTraits
{
    // What we want to know in this line is whether the object is const, because
    // that makes even nonconst member fields also const.  For SFINAE, we need to make it a
    // pointer or pointer-to-const, whether or not CallAs is actually a reference or pointer.
    typedef typename boost::remove_reference<typename boost::remove_pointer<CallAs>::type>::type* ObjPtr;

    // A helper type that wraps up all values of the variable's traits.
    // Size_ is for bounds checking for arrays.  If not an array or size is unknown, -1 disables bounds checking.
    template <bool is_const_, typename R_, typename ClassT_, int Size_=-1>
    struct Sig
    {
        enum { is_const = is_const_ };

        typedef R_ R;
        typedef ClassT_ ClassT;

        // For arrays, stores the number of elements in the array
        enum { Size = Size_ };
    };

    // One of the following test() functions will correspond to the type F:

    // Nonconst member variables.
    template <typename R, typename ClassT>
    static Sig<false, R, ClassT> test(R ClassT::*f, ClassT* o);

    // Const member variables.
    template <typename R, typename ClassT>
    static Sig<true, R const, ClassT> test(const R ClassT::*f, ClassT* o);

    // Static member variables and ordinary (namespace-level) variables.
    template <typename R>
    static Sig<false, R, StaticField> test(R *f, StaticField* o);

    // Const static member variables and const ordinary (namespace-level) variables.
    template <typename R>
    static Sig<true, R const, StaticField> test(const R *f, StaticField* o);


    // for arrays:  we want R to be the type of an array element, not an array itself.

    // Nonconst member variables.
    template <typename R, typename ClassT, int N>
    static Sig<false, R, ClassT> test(R (ClassT::*f)[N], ClassT* o);

    // Const member variables.
    template <typename R, typename ClassT, int N>
    static Sig<true, R const, ClassT> test(const R (ClassT::*f)[N], ClassT* o);

    // Static member variables and ordinary (namespace-level) variables.
    template <typename R, int N>
    static Sig<false, R, StaticField, N> test(R (*f)[N], StaticField* o);

    // Const static member variables and const ordinary (namespace-level) variables.
    template <typename R, int N>
    static Sig<true, R const, StaticField, N> test(const R (*f)[N], StaticField* o);


    /////////////////////////////////////////////////////////
    // For const objects:  the field reference is also const.
    /////////////////////////////////////////////////////////

    // Nonconst member variables.
    template <typename R, typename ClassT>
    static Sig<false, R const&, ClassT> test(R ClassT::*f, ClassT const* o);

    // Const member variables.
    template <typename R, typename ClassT>
    static Sig<true, R const&, ClassT> test(const R ClassT::*f, ClassT const* o);

    // for arrays:  we want R to be the type of an array element, not an array itself.

    // Nonconst member variables.
    template <typename R, typename ClassT, int N>
    static Sig<false, R const&, ClassT, N> test(R (ClassT::*f)[N], ClassT const* o);

    // Const member variables.
    template <typename R, typename ClassT, int N>
    static Sig<true, R const&, ClassT, N> test(const R (ClassT::*f)[N], ClassT const* o);

    // StaticFields cannot have const objects, because they do not really have an object at all!

    ///////////////////////
    // END CONST OBJECTS
    ///////////////////////

    // Figure out what result of invoking test() on a pointer of type "F" would be.
    typedef decltype(test(F(0), ObjPtr(0))) Signature;

    // Return value of the function.
    typedef typename Signature::R R;

    // Target object of the function.  "void" if not a nonstatic member function.
    typedef typename Signature::ClassT ClassT;

    enum { is_const = Signature::is_const };

    enum { Size = Signature::Size };
};

}}
