// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/TypeConv/TypeConvGraph.hpp"

#include "boost/graph/breadth_first_search.hpp"
#include <iostream>

#include "boost/config.hpp"

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <limits>

#include "boost/graph/visitors.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/breadth_first_search.hpp"
//#include <boost/property_map/property_map.hpp>
#include "boost/graph/graph_utility.hpp"

#include "boost/graph/breadth_first_search.hpp"

#include "boost/lexical_cast.hpp"

#include <assert.h>

using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;

namespace LikeMagic { namespace TypeConv {

TypeConvGraph::TypeConvGraph()
    : no_vertex(std::numeric_limits<vertex_t>::max())
{
}

TypeConvGraph::~TypeConvGraph()
{
    // Causes a seg fault in Term for some reason.
//    auto edge_range = edges(graph);
//    for (auto it=edge_range.first; it!=edge_range.second; it++)
//        delete graph[*it].conv;
}

void TypeConvGraph::print_graph() const
{
    boost::print_graph(graph);
}

bool TypeConvGraph::has_type(TypeInfoKey type) const
{
    return vertex_map.find(type) != vertex_map.end();
}

TypeConvGraph::vertex_t TypeConvGraph::add_type(TypeInfoPtr type)
{
    if (!has_type(type))
    {
        vertex_map[make_key_wrapper(type)] = add_vertex(graph);
    }

    return vertex_map[make_key_wrapper(type)];
}

void TypeConvGraph::add_conv(TypeInfoPtr from, TypeInfoPtr to, p_conv_t conv)
{
    auto from_vert = add_type(from);
    auto to_vert = add_type(to);

    if (!edge(from_vert, to_vert, graph).second)
        graph[add_edge(from_vert, to_vert, graph).first].conv = conv;
}

struct FindType
{
    struct TypeFoundException { std::string msg; TypeFoundException(std::string msg_) : msg(msg_) {}; };

    typedef boost::on_finish_vertex event_filter;
    TypeConvGraph::vertex_t dest;
    bool& found_conv;

    FindType(TypeConvGraph::vertex_t dest_, bool& found_conv_)
        : dest(dest_), found_conv(found_conv_) {}

    template <class Vertex, class Graph>
    void operator()(Vertex u, const Graph&)
    {
        if (u == dest)
        {
            found_conv = true;
            throw TypeFoundException("Found: " + boost::lexical_cast<std::string>(u));
        }
    }
};

ExprPtr TypeConvGraph::build_conv_chain(ExprPtr from_expr, TypeConvGraph::p_chain_t chain) const
{
    auto expr = from_expr;

    for (size_t i=0; i < chain->size(); i++)
    {
        expr = (*chain)[i]->wrap_expr(expr);
    }

    return expr;
}


ExprPtr TypeConvGraph::wrap_expr(ExprPtr from_expr, TypeInfoPtr from, TypeInfoPtr to) const
{
    auto result = search_for_conv(from, to);

    if (!result)
        throw std::logic_error(std::string("No type conversion path from ") + from->describe() + " to " + to->describe());

    return build_conv_chain(from_expr, result);
}


bool TypeConvGraph::has_conv(TypeInfoPtr from_type, TypeInfoPtr to_type) const
{
    return search_for_conv(from_type, to_type) != NULL;
}


TypeConvGraph::p_chain_t  TypeConvGraph::search_for_conv(TypeInfoKey from, TypeInfoKey to) const
{
    static int count = 0;

    auto key = std::make_pair(from, to);

    // If not cached
    if (conv_cache.find(key) == conv_cache.end())
    {

        if (!has_type(from) || !has_type(to))
            throw std::logic_error("From or to type not found in TypeConvGraph in search_for_conv from " + from.key->describe() + " to " + to.key->describe());

        vertex_t source = vertex_map.find(from)->second;
        vertex_t dest = vertex_map.find(to)->second;

        std::vector<vertex_t> pred(boost::num_vertices(graph));

        // Clear dest so we know if we reached it or not.
        pred[dest] = no_vertex;

        // Optional?
        for (size_t i=0; i<pred.size(); i++)
            pred[i] = no_vertex;

        bool found_conv = false;
        FindType finder(dest, found_conv);

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
                            finder,
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
        catch (FindType::TypeFoundException const& tfe)
        {
            //std::cout << "Found the type. " << tfe.msg << std::endl;
        }
        catch (...)
        {
            //std::cout << "Unknown exception in type conv graph search." << std::endl;
        }

        if (!finder.found_conv || pred[dest] == no_vertex)
            return conv_cache[key] = p_chain_t();
        else
        {
            p_chain_t result(new std::vector<p_conv_t>);

            for (vertex_t cur=dest; cur != pred[cur]; cur=pred[cur])
                result->push_back(graph[edge(pred[cur], cur, graph).first].conv);

            reverse(result->begin(), result->end());

            conv_cache[key] = result;
        }

    }

    return conv_cache[key];
}



}}
