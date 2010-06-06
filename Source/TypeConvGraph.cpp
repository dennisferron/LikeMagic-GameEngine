#include "LikeMagic/TypeConv/TypeConvGraph.hpp"

#include "boost/graph/breadth_first_search.hpp"

using namespace LikeMagic::SFMO;

namespace LikeMagic { namespace TypeConv {

bool TypeConvGraph::has_type(BetterTypeInfo type) const
{
    return vertex_map.find(type) != vertex_map.end();
}

void TypeConvGraph::add_type(BetterTypeInfo type)
{
    if (!has_type(type))
        vertex_map[type] = add_vertex(graph);
}

void TypeConvGraph::add_conv(BetterTypeInfo from, BetterTypeInfo to, AbstractTypeConverter const* conv)
{
    add_type(from);
    add_type(to);
    // TODO:  figure out correct syntax for accessing the edge property.
    //add_edge(vertex_map[from], vertex_map[to], graph).second.conv = conv;
}

struct ConvChainBuilder : public boost::default_bfs_visitor
{
    TypeConvGraph::vertex_t dest;
    std::vector<AbstractTypeConverter const*> chain;

    ConvChainBuilder(TypeConvGraph::vertex_t dest_)
        : dest(dest_) {}

    template <class Vertex, class Graph>
    void discover_vertex(Vertex u, Graph& g)
    {
        if (u == dest)
            throw chain;
    }

    template <typename Edge, typename Graph>
    void tree_edge(Edge e, const Graph& g) const
    {
        // TODO: Figure out how to access the type conv object from the edge.
        //chain.push_back(e.conv);
    }
};

ExprPtr TypeConvGraph::use_conv_chain(ExprPtr from, conv_vect_t const& chain, size_t pos)
{
    return
        pos == chain.size()?
            from
        :
            chain[pos]->wrap_expr(
                use_conv_chain(from, chain, pos+1));
}

ExprPtr TypeConvGraph::wrap_expr(ExprPtr from_expr, BetterTypeInfo from, BetterTypeInfo to) const
{
    vertex_t source = vertex_map.find(from)->second;
    vertex_t dest = vertex_map.find(to)->second;

    try
    {
        breadth_first_search(graph, source, visitor(ConvChainBuilder(dest)));
    }
    catch (conv_vect_t const& chain)
    {
        return use_conv_chain(from_expr, chain);
    }
    throw std::logic_error(std::string("No type conversion path connecting ") + from.describe() + " to " + to.describe());

}

}}
