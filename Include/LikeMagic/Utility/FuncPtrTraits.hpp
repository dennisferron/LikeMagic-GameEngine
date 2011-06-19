// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
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

template <typename FirstArg, typename... Args>
TypeInfoList make_arg_list(TypePack<FirstArg, Args...> args)
{
    TypeInfoList list;
    list.push_back(BetterTypeInfo::create_index<FirstArg>());
    TypeInfoList others = make_arg_list(TypePack<Args...>());
    list.insert(list.end(), others.begin(), others.end());
    return list;
}

inline TypeInfoList make_arg_list(TypePack<> args)
{
    return TypeInfoList();
}


// A dummy type used to indicate that a function is a static class method
// or a global C++ function that doesn't have an object associated with it.
struct StaticMethod {};

template <typename F>
struct FuncPtrTraits
{

    // A helper type that wraps up all values of the function traits.
    template <bool is_const_, bool is_static_, typename R_, typename ObjT_, typename... Args_>
    struct Sig
    {
        enum { is_const = is_const_ };
        enum { is_static = is_static_ };
        enum { num_args = sizeof...(Args_) };

        typedef R_ R;
        typedef ObjT_ ObjT;

        // Applies the template "Each" to each arg type & then rolls them up into the "All" template.
        template <template <typename A> class Each, template<typename... Args> class All>
        struct ConvertArgTypes { typedef All<Each<Args_>...> type; };

        // Creates an index pack for the number of args.
        typedef typename MakeIndexPack<sizeof...(Args_)>::type IPack;

        typedef TypePack<Args_...> TPack;
    };

    // One of the following 3 test() functions will correspond to the type F:

    // Nonconst member functions.
    template <typename R, typename ObjT, typename... Args>
    static Sig<false, false, R, ObjT, Args...> test(R (ObjT::*f)(Args...));

    // Const member functions.
    template <typename R, typename ObjT, typename... Args>
    static Sig<true, false, R, ObjT, Args...> test(R (ObjT::*f)(Args...) const);

    // Static member functions and ordinary (namespace-level) functions.
    template <typename R, typename... Args>
    static Sig<false, true, R, StaticMethod, Args...> test(R (*f)(Args...));

    // Figure out what result of invoking test() on a pointer of type "F" would be.
    typedef decltype(test(F(0))) Signature;

    // Return value of the function.
    typedef typename Signature::R R;

    // Target object of the function.  "void" if not a nonstatic member function.
    typedef typename Signature::ObjT ObjT;

    // Applies the template "Each" to each arg type & then rolls them up into the "All" template.
    // Default value of "All" is to turn the result into a tuple.
    //template <template <typename A> class Each, template<typename... Args> class All=std::tuple>
    //struct ConvertArgTypes { typedef Signature::template ConvertArgTypes<Each, All>::type type; }

    // An index pack to use to index the args 0...(N-1).
    typedef typename Signature::IPack IPack;

    // Used to represent the types of the arguments to the function.
    typedef typename Signature::TPack TPack;

    enum { is_const = Signature::is_const };
    enum { is_static = Signature::is_static };
    enum { num_args = Signature::num_args };

    // Get a list of type info for at most the first N arg types.
    static TypeInfoList get_arg_types()
    {
        return make_arg_list(TPack());
    }

};

}}
