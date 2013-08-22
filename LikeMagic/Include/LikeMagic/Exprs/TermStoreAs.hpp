// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

namespace LM {

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

// Still necessary?
template <> struct TermStoreAs<bool&> { typedef bool type; };

}
