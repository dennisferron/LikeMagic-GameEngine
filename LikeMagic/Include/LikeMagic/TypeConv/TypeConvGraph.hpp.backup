
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

struct FindType;

class TypeConvGraph
{
private:
    // To give it acess to our private typedefs.
    friend struct FindType;

    typedef AbstractTypeConverter const* p_conv_t;

    struct edge_info
    {
        p_conv_t conv;
    };

    struct vertex_info
    {
        BetterTypeInfo type;
    };

    typedef adjacency_list<vecS, vecS, undirectedS, vertex_info, edge_info> graph_t;
    typedef graph_traits<graph_t>::vertex_descriptor vertex_t;
    typedef graph_traits<graph_t>::edge_descriptor edge_t;
    typedef std::map<BetterTypeInfo, vertex_t> vertex_map_t;

    graph_t graph;
    vertex_map_t vertex_map;

    bool has_type(BetterTypeInfo type) const;
    void add_type(BetterTypeInfo type);

    ExprPtr build_conv_chain(ExprPtr from_expr, vertex_t cur, std::vector<vertex_t> const& pred_list) const;

public:
    void add_conv(BetterTypeInfo from, BetterTypeInfo to, AbstractTypeConverter const* conv);
    ExprPtr wrap_expr(ExprPtr from_expr, BetterTypeInfo from, BetterTypeInfo to) const;
    void print_graph() const;
};

}}
