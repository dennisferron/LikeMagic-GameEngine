
#pragma once

#include <utility> // std::pair
#include <map>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

#include "AbstractTypeConverter.hpp"

namespace LikeMagic { namespace TypeConv {

class TypeConvGraph
{
private:
    std::map<BetterTypeInfo, int> indexes;

    struct edge_info
    {
        AbstractTypeConverter const* conv;
    };

    typedef adjacency_list<vecS, vecS, undirectedS, no_property, edge_info> graph_t;
    graph_t graph;

    void add_type(BetterTypeInfo type);

public:
    void add_conv(BetterTypeInfo from, BetterTypeInfo to, AbstractTypeConverter const* conv);
    ExprPtr wrap_expr(ExprPtr from, BetterTypeInfo from, BetterTypeInfo to) const;
};


}}
