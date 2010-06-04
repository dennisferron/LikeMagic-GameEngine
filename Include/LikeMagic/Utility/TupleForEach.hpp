#pragma once

#include <tuple>

#include "IndexPack.hpp"

namespace LikeMagic { namespace Utility {



template <int I, typename Tuple>
struct TupleForEach : private TupleForEach<I-1, Tuple>
{
    template <typename Functor>
    TupleForEach(Functor& f, const Tuple& t)
        : TupleForEach<I-1, Tuple>(f, t)
            { f(std::get<I-1>(t)); }
};

template <typename Tuple>
struct TupleForEach<0, Tuple>
{
    template <typename Functor>
    TupleForEach(Functor& f, const Tuple& t) {}
};

template <typename Functor, typename... T>
void tuple_for_each(Functor& f, const std::tuple<T...>& t)
{
    TupleForEach<sizeof...(T), std::tuple<T...>>(f, t);
}



template <int I, typename Tuple>
struct TupleForEachPairInSeq : private TupleForEachPairInSeq<I-1, Tuple>
{
    template <typename Functor>
    TupleForEachPairInSeq(Functor& f, const Tuple& t)
        : TupleForEachPairInSeq<I-1, Tuple>(f, t)
            { f(std::get<I-1>(t), std::get<I-2>(t)); }
};

template <typename Tuple>
struct TupleForEachPairInSeq<1, Tuple>
{
    template <typename Functor>
    TupleForEachPairInSeq(Functor& f, const Tuple& t) {}
};

template <typename Tuple>
struct TupleForEachPairInSeq<0, Tuple>
{
    template <typename Functor>
    TupleForEachPairInSeq(Functor& f, const Tuple& t) {}
};

template <typename Functor, typename... T>
void tuple_for_each_pair_in_seq(Functor& f, const std::tuple<T...>& t)
{
    TupleForEachPairInSeq<sizeof...(T), std::tuple<T...>>(f, t);
}



/*

template <typename Functor, typename... T, int... Indices>
void tuple_for_each_index(Functor f, const std::tuple<T...>& t, IndexPack<Indices...>)
{
    f(std::get<Indices>(t));...
}

template <typename Functor, typename... T>
void tuple_for_each(Functor f, const std::tuple<T...>& t)
{
    typedef typename MakeIndexPack<sizeof...(T)>::type IPack;
    tuple_for_each_index(f, t, IPack());
}

*/

}}
