// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/TypeConv/TypeConvGraph.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/Exprs/BottomPtrExpr.hpp"

//#include "boost/graph/breadth_first_search.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include <iostream>

#include "boost/config.hpp"

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <limits>
using namespace std;

#include "boost/graph/visitors.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include "boost/lexical_cast.hpp"

#include <assert.h>

using namespace boost;

using namespace LikeMagic::Exprs;
using namespace LikeMagic::Utility;

namespace LikeMagic { namespace TypeConv {

TypeConvGraph::TypeConvGraph()
    : no_vertex(std::numeric_limits<vertex_t>::max()), bot_conv(new NoChangeConv<>())
{
}

TypeConvGraph::~TypeConvGraph()
{
    // You don't delete these because they're held by smart pointers which delete them for you!
    //xx  auto edge_range = edges(graph);
    //xx  for (auto it=edge_range.first; it!=edge_range.second; it++)
    //xx     delete graph[*it].conv;
}

void TypeConvGraph::print_graph() const
{
    boost::print_graph(graph);
}

bool TypeConvGraph::has_type(TypeIndex type) const
{
    std::size_t pos = type.get_id();
    std::size_t sz = has_vertex.size();
    return pos < sz && has_vertex[pos];
}

TypeConvGraph::vertex_t TypeConvGraph::add_type(TypeIndex type)
{
    std::size_t pos = type.get_id();

    if (!has_type(type))
    {
        if (pos >= has_vertex.size())
        {
            vertex_map.resize(pos+1);
            has_vertex.resize(pos+1, false);
        }

        vertex_map[pos] = add_vertex(graph);
        has_vertex[pos] = true;
    }

    return vertex_map[pos];
}

void TypeConvGraph::add_conv(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    auto from_vert = add_type(from);
    auto to_vert = add_type(to);

    if (!edge(from_vert, to_vert, graph).second)
    {
        auto new_edge = add_edge(from_vert, to_vert, graph).first;
        graph[new_edge].conv = conv;
        graph[new_edge].cost = conv->cost();
    }
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

            // I believe Djikstra's shortest paths requires NOT doing an early exit,
            // and anyway not throwing here allows us to turn "Catch C++ Exceptions"
            // back on in code::blocks to catch error exceptions.
            //throw TypeFoundException("Found: " + boost::lexical_cast<std::string>(u));
        }
    }
};

ExprPtr TypeConvGraph::build_conv_chain(ExprPtr from_expr, TypeConvGraph::p_chain_t const& chain) const
{
    auto expr = from_expr;

    for (size_t i=0; i < chain->size(); i++)
    {
        expr = (*chain)[i]->wrap_expr(expr);
    }

    //std::cout << "Built conv chain: " << expr->description() << std::endl;

    return expr;
}

void TypeConvGraph::print_conv_chain(TypeIndex from, TypeIndex to) const
{
    p_chain_t const& chain = search_for_conv(from, to);

    if (!chain)
    {
        cout << "No conversion chain from " << from.describe() << " to " << to.describe() << endl;
    }
    else
    {
        cout << "Conversion chain from " << from.describe() << " to " << to.describe() << " is ";
        print_conv_chain(chain);
    }

}

void TypeConvGraph::print_conv_chain(p_chain_t const& chain) const
{
    for (size_t i=0; i < chain->size(); i++)
    {
        cout  << " -> "<< (*chain)[i]->describe();
    }
    cout << endl;
}


ExprPtr TypeConvGraph::wrap_expr(ExprPtr from_expr, TypeIndex from, TypeIndex to) const
{
    p_chain_t const& result = search_for_conv(from, to);

    if (!result)
    {
        std::string msg  = std::string("No type conversion path from ") + from.describe() + " to " + to.describe() + ".  ";

        try
        {
            if (search_for_conv(from.get_info()->as_nonconst_obj_type()->get_index(), to))
                msg += "I notice the conversion would work if the from-type were not const.  Did you use get_fieldName (const version) when you meant to use ref_fieldName (nonconst version)?  Or call functionName_nc (nonconst version) when you meant to call functioname_c (const version)?  Don't forget that a member of a const object is also const.";
        }
        catch (...)
        {
            // as_nonconst_type can fail for types that are not C++ types.  We need to catch that exception and ignore it so that we don't lose the more important original exception message.
        }


        throw std::logic_error(msg);
    }

    // Debugging
    //print_conv_chain(result);

    return build_conv_chain(from_expr, result);
}


bool TypeConvGraph::has_conv(TypeIndex from_type, TypeIndex to_type) const
{
    return search_for_conv(from_type, to_type) != NULL;
}


TypeConvGraph::p_chain_t const& TypeConvGraph::search_for_conv(TypeIndex from, TypeIndex to) const
{
    // Why was this set if not used?
    //static TypeIndex bot = BetterTypeInfo::create_index<BottomPtrType>();

    static int count = 0;

    auto key = std::make_pair(from, to);

    // If not cached
    if (conv_cache.find(key) == conv_cache.end())
    {
        int count=0;
        for (std::size_t i=0; i<has_vertex.size();i++)
            if (!has_vertex[i])
                ++count;

        if (!has_type(from))
            throw std::logic_error("From type not found in TypeConvGraph in search_for_conv from " + from.describe() + " to " + to.describe());

        if (!has_type(to))
            throw std::logic_error("To type not found in TypeConvGraph in search_for_conv from " + from.describe() + " to " + to.describe());

        vertex_t source = vertex_map[from.get_id()];
        vertex_t dest = vertex_map[to.get_id()];

        std::vector<vertex_t> pred(boost::num_vertices(graph));

        // Clear dest so we know if we reached it or not.
        pred[dest] = no_vertex;

        // Optional?
        for (size_t i=0; i<pred.size(); i++)
            pred[i] = no_vertex;

        bool found_conv = false;
        FindType finder(dest, found_conv);

        // Marker for the (beginning) end of the chain
        pred[source] = source;

        // Will it default to something sensible if I don't pass a distance map?
        vector<float> distances(num_vertices(graph));

        dijkstra_shortest_paths
        (
            graph,
            source,
            predecessor_map
            (
                &pred[0]
            )
            .
            weight_map
            (
                get
                (
                    &edge_info::cost,
                    graph
                )
            )
            .
            distance_map
            (
                make_iterator_property_map
                (
                    distances.begin(),
                    get
                    (
                        vertex_index,
                        graph
                    )
                )
            )
            .
            visitor
            (
                make_dijkstra_visitor(finder)
            )
        );

        if (!finder.found_conv || pred[dest] == no_vertex)
        {
            conv_cache[key] = std::move(p_chain_t()); // NULL
            return conv_cache[key];
        }
        else
        {
            p_chain_t result(new std::vector<p_conv_t>);

            for (vertex_t cur=dest; cur != pred[cur]; cur=pred[cur])
                result->push_back(graph[edge(pred[cur], cur, graph).first].conv);

            reverse(result->begin(), result->end());

            conv_cache[key] = std::move(result);
        }
    }

    return conv_cache[key];
}




}}
