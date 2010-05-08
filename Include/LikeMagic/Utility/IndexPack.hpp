
#pragma once

namespace LikeMagic { namespace Utility {

// Given an integer N, "pops" N-1 and pastes it on front of Tail; repeats with N diminishing.
template<int N, int... Tail>
struct MakeIndexPack : MakeIndexPack<N-1,N-1,Tail...>
{};

// Used to create a sequence of arg indexes (0, 1, ...) for use in
// variadic template expansions to coincide with the arg type expansion.
template <int... Idx> struct IndexPack {};

// When N is 0, we are done and Tail contains all the numbers in ascending order.
template<int... Tail>
struct MakeIndexPack<0,Tail...>
{
    typedef IndexPack<Tail...> type;
};

}}
