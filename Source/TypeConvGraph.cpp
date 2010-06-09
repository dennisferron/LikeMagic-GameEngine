#include "LikeMagic/TypeConv/TypeConvGraph.hpp"

#include "boost/graph/breadth_first_search.hpp"
#include <iostream>

#include <boost/config.hpp>

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>

#include <boost/graph/visitors.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_utility.hpp>

#include "LikeMagic/TypeConv/TypeConvGraph.hpp"

#include "boost/graph/breadth_first_search.hpp"

using namespace LikeMagic::SFMO;

namespace LikeMagic { namespace TypeConv {

void TypeConvGraph::print_graph() const
{
    boost::print_graph(graph);
}

bool TypeConvGraph::has_type(BetterTypeInfo type) const
{
    return vertex_map.find(type) != vertex_map.end();
}

void TypeConvGraph::add_type(BetterTypeInfo type)
{
    if (!has_type(type))
        vertex_map[type] = add_vertex(graph);
}

void TypeConvGraph::add_conv(BetterTypeInfo from, BetterTypeInfo to, p_conv_t conv)
{
    add_type(from);
    add_type(to);
    graph[add_edge(vertex_map[from], vertex_map[to], graph).first].conv = conv;
}

struct FindType
{
    struct TypeFoundException {};

    typedef boost::on_finish_vertex event_filter;
    TypeConvGraph::vertex_t dest;

    FindType(TypeConvGraph::vertex_t dest_)
        : dest(dest_) {}

    template <class Vertex, class Graph>
    void operator()(Vertex u, const Graph&)
    {
        if (u == dest)
            throw TypeFoundException();
    }
};

ExprPtr TypeConvGraph::build_conv_chain(ExprPtr from_expr, vertex_t cur, std::vector<vertex_t> const& pred_list) const
{
    vertex_t pred = pred_list[cur];

    if (pred == cur)
        return from_expr;
    else
    {
        AbstractTypeConverter const* conv = graph[edge(pred, cur, graph).first].conv;
        std::cout << conv->describe() << std::endl;
        return conv->wrap_expr(build_conv_chain(from_expr, pred, pred_list));
    }
}

ExprPtr TypeConvGraph::wrap_expr(ExprPtr from_expr, BetterTypeInfo from, BetterTypeInfo to) const
{
    vertex_t source = vertex_map.find(from)->second;
    vertex_t dest = vertex_map.find(to)->second;
    std::vector<vertex_t> pred(boost::num_vertices(graph));

    for (size_t i=0; i<pred.size(); i++)
        pred[i] = -1;

    try
    {
        pred[source] = source;
        boost::breadth_first_search
        (
            graph,
            source,
            boost::visitor
            (
                boost::make_bfs_visitor
                (
                    std::make_pair
                    (
                        FindType(dest),
                        boost::record_predecessors
                        (
                            &pred[0],
                            boost::on_tree_edge()
                        )
                    )
                )
            )
        );
    }
    catch (FindType::TypeFoundException const&)
    {
        ExprPtr expr = build_conv_chain(from_expr, dest, pred);
        std::cout << expr->description() << std::endl;
        return expr;
    }
    throw std::logic_error(std::string("No type conversion path connecting ") + from.describe() + " to " + to.describe());

}


}}
