
#pragma once

#include <utility> // std::pair
#include <map>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"
#include "LikeMagic/SFMO/AbstractExpression.hpp"

namespace LikeMagic { namespace TypeConv {

using LikeMagic::Utility::BetterTypeInfo;
using namespace boost::graph;

struct ConvChainBuilder;

class TypeConvGraph
{
private:
    // To give it acess to our private typedefs.
    friend struct ConvChainBuilder;

    typedef AbstractTypeConverter const* p_conv_t;
    typedef std::vector<p_conv_t> conv_vect_t;

    struct edge_info
    {
        p_conv_t conv;
    };

    typedef adjacency_list<vecS, vecS, undirectedS, no_property, edge_info> graph_t;
    typedef graph_traits<graph_t>::vertex_descriptor vertex_t;
    typedef std::map<BetterTypeInfo, vertex_t> vertex_map_t;

    graph_t graph;
    vertex_map_t vertex_map;

    bool has_type(BetterTypeInfo type) const;
    void add_type(BetterTypeInfo type);

    static ExprPtr use_conv_chain(ExprPtr from, conv_vect_t const& chain, size_t pos=0);

public:
    void add_conv(BetterTypeInfo from, BetterTypeInfo to, AbstractTypeConverter const* conv);
    ExprPtr wrap_expr(ExprPtr from_expr, BetterTypeInfo from, BetterTypeInfo to) const;
};


}}
