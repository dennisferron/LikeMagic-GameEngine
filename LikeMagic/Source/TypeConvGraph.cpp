// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/TypeConv/TypeConvGraph.hpp"
#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "boost/graph/dijkstra_shortest_paths.hpp"
#include <iostream>

#include "LikeMagic/Exceptions/Exception.hpp"

#include "boost/config.hpp"

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>
#include <limits>
#include <sstream>
using namespace std;

#include "boost/graph/visitors.hpp"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graph_utility.hpp"
#include "boost/graph/graphviz.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include "boost/lexical_cast.hpp"

#include <assert.h>

using namespace boost;

using namespace LM;

static string describe_type(TypeIndex type)
{
    stringstream ss;
    ss << type.description();
    ss << " type id:";
    ss << type.get_id();
    return ss.str();
}

namespace LM {

TypeConvGraph::TypeConvGraph()
    : no_vertex(std::numeric_limits<vertex_t>::max()), bot_conv(new NoChangeConv("Bottom type conv")), recheck_failed_convs(true)
{
}

TypeConvGraph::~TypeConvGraph()
{
    // You don't delete these because they're held by smart pointers which delete them for you!
    //xx  auto edge_range = edges(graph);
    //xx  for (auto it=edge_range.first; it!=edge_range.second; it++)
    //xx     delete graph[*it].conv;
}

class EdgePropertyWriter {
public:
     EdgePropertyWriter(TypeConvGraph::graph_t graph_, TypeConvGraph::vertex_map_t const& vertex_map_)
        : graph(graph_), vertex_map(vertex_map_) {}
     template <class VertexOrEdge>
     void operator()(std::ostream& out, const VertexOrEdge& v) const {
            TypeIndex from = graph[v.m_source].type;
            TypeIndex to = graph[v.m_target].type;

            //TypeIndex from2 = graph[vertex_map[v.m_source]].type;
            //TypeIndex to2 = graph[vertex_map[v.m_target]].type;

            std::string from_descr;
            try { from_descr = from.description(); } catch (...) { from_descr = "invalid"; }

            std::string to_descr;
            try { to_descr = to.description(); } catch (...) { to_descr = "invalid"; }

            out << "[description=\"" << graph[v].conv->description()
                << " from " /*<< v.m_source*/ << from_descr << " (" << from.get_id() << ")"
                << " to " /*<< v.m_target*/ << to_descr << " (" << to.get_id() << ")"
                << "\"]";
     }
private:
     TypeConvGraph::graph_t& graph;
     TypeConvGraph::vertex_map_t const& vertex_map;
};

void TypeConvGraph::print_graph() const
{
    //boost::print_graph(graph);
    EdgePropertyWriter w(graph, vertex_map);
    //ofstream outf("net.gv");
    boost::write_graphviz(cout, graph, boost::default_writer(), w);
}

bool TypeConvGraph::has_type(TypeIndex type) const
{
    std::size_t pos = type.get_id();
    std::size_t sz = has_vertex.size();

    bool result = pos < sz && has_vertex[pos];

    /*
    if (!result)
    {
        cout << "has_type pos=" << pos << " sz=" << sz;
        if (pos < sz)
            cout << " has_vertex=" << has_vertex[pos];
        else
            cout << " !(pos<sz)";
        cout << endl;
        cout << "has_type result = " << result << endl;
    }
    */

    return result;
}

TypeConvGraph::vertex_t TypeConvGraph::add_type(TypeIndex type)
{
    //cout << "add_type " << describe_type(type) << endl;

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
        graph[vertex_map[pos]].type = type;
    }

    return vertex_map[pos];
}

bool TypeConvGraph::has_direct_conv(TypeIndex from_type, TypeIndex to_type) const
{
    if (!has_type(from_type) || !has_type(to_type))
        return false;

    std::size_t from_pos = from_type.get_id();
    auto from_vert = vertex_map[from_pos];
    std::size_t to_pos = to_type.get_id();
    auto to_vert = vertex_map[from_pos];
    auto existing_edge = edge(from_vert, to_vert, graph);
    return existing_edge.second;
}

void TypeConvGraph::add_conv(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    if (!recheck_failed_convs)
    {
        std::string msg = "A type converter from "
            + from.description() + " to " + to.description()
            + " called " + conv->description()
            + " was added after recheck_failed_convs flag was cleared."
            + "  You must only clear recheck_failed_convs after all the "
            + " type converters are done being added.";
        cout << msg << endl;
        throw std::logic_error(msg);
    }

    if (from.get_info().ref_type == RefType::Metaclass)
    {
        std::string msg = "add_conv from_type is metaclass when adding type converter from "
            + describe_type(from) + " to " + describe_type(to)
            + " called " + conv->description();
        cout << msg << endl;
        throw std::logic_error(msg);
    }

    if (to.get_info().ref_type == RefType::Metaclass)
    {
        std::string msg = "add_conv to_type is metaclass when adding type converter from "
            + describe_type(from) + " to " + describe_type(to)
            + " called " + conv->description();
        cout << msg << endl;
        throw std::logic_error(msg);
    }

    //cout << "about to add_conv from typeindex " << from.get_id() << " to typeindex " << to.get_id() << endl;

    auto from_vert = add_type(from);
    auto to_vert = add_type(to);
    auto existing_edge = edge(from_vert, to_vert, graph);

    if (existing_edge.second)
    {
        std::string msg = "Already have a type converter from "
            + from.description() + " to " + to.description()
            + " called " + graph[existing_edge.first].conv->description()
            + " when trying to add " + conv->description();
        cout << msg << endl;
        throw std::logic_error(msg);
    }
    else
    {
        auto new_edge = add_edge(from_vert, to_vert, graph).first;
        graph[new_edge].conv = conv;
        graph[new_edge].cost = conv->cost();

/*
        cout << "Added type converter from "
            << from.description() << " " << from.get_id() << " to " << to.description() << " " << to.get_id()
            << " called " << conv->description() << endl;
*/
    }
}

TypeConvGraph::p_conv_t TypeConvGraph::get_conv(TypeIndex from, TypeIndex to) const
{
    std::size_t from_pos = from.get_id();
    auto from_vert = vertex_map[from_pos];

    std::size_t to_pos = to.get_id();
    auto to_vert = vertex_map[to_pos];

    if (edge(from_vert, to_vert, graph).second)
    {
        auto new_edge = edge(from_vert, to_vert, graph).first;
        return graph[new_edge].conv;
    }
    else
    {
        return nullptr;
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
        cout << "No conversion chain from " << from.description() << " to " << to.description() << endl;
    }
    else
    {
        cout << "Conversion chain from " << from.description() << " to " << to.description() << " is ";
        print_conv_chain(chain);
    }

}

void TypeConvGraph::print_conv_chain(p_chain_t const& chain) const
{
    cout << "TypeConv chain, length " << chain->size() << " chain is {";
    for (size_t i=0; i < chain->size(); i++)
    {
        cout  << " -> " << (*chain)[i]->description();
    }
    cout << " }" << endl;
}

ExprPtr TypeConvGraph::wrap_expr(ExprPtr from_expr, TypeIndex from, TypeIndex to) const
{
    p_chain_t const& result = search_for_conv(from, to);

    if (!result)
    {
        std::string msg  = std::string("No type conversion path from ") + describe_type(from)
            + " to " + describe_type(to) + ".  ";
        cout << msg << endl;

        TypeInfo from_info = from.get_info();
        if (from_info.ref_type == RefType::RefToConst || from_info.ptr_type == PtrType::PtrToConst)
        {
            // TODO:  This actually only accounts for ref, so also add ptr to nonconst if it is a ptr.
            TypeIndex from_as_nonconst = get_index(from_info.as_ref_to_nonconst());
            if (has_type(from_as_nonconst) && search_for_conv(from_as_nonconst, to))
                msg += "I notice the conversion would work if the from-type were not const.  Did you use get_fieldName (const version) when you meant to use ref_fieldName (nonconst version)?  Or call functionName_nc (nonconst version) when you meant to call functioname_c (const version)?  Don't forget that a member of a const object is also const.";
        }

        throw std::logic_error(msg);
    }

    // Debugging
    //cout << "Type conversion chain from " << from.description() << " to " << to.description() << " ";
    //print_conv_chain(result);

    return build_conv_chain(from_expr, result);
}

bool TypeConvGraph::has_conv(TypeIndex from_type, TypeIndex to_type) const
{
    return has_type(from_type) && has_type(to_type)
        && (search_for_conv(from_type, to_type) != nullptr);
}

TypeConvGraph::p_chain_t const& TypeConvGraph::search_for_conv(TypeIndex from, TypeIndex to) const
{
    auto key = std::make_pair(from.get_id(), to.get_id());

    bool not_in_cache = false;
    bool null_in_cache = false;

    // If not cached
    if ( (not_in_cache = (conv_cache.find(key) == conv_cache.end())) || ((null_in_cache = (conv_cache[key] == nullptr) && recheck_failed_convs)))
    {
        if (!has_type(from) && !has_type(to))
        {
            string msg = "From and To types not found in TypeConvGraph in search_for_conv from " + describe_type(from) + " to " + describe_type(to);
            cout << msg << endl;
            throw LM::Exception(msg);
        }

        if (!has_type(from))
        {
            string msg = "From type not found in TypeConvGraph in search_for_conv from " + describe_type(from) + " to " + describe_type(to);
            cout << msg << endl;
            throw LM::Exception(msg);
        }

        if (!has_type(to))
        {
            string msg = "To type not found in TypeConvGraph in search_for_conv from " + describe_type(from) + " to " + describe_type(to);
            cout << msg << endl;
            throw LM::Exception(msg);
        }

        vertex_t source = vertex_map[from.get_id()];
        vertex_t dest = vertex_map[to.get_id()];

        std::vector<vertex_t> pred(boost::num_vertices(graph));

        // Clear dest so we know if we reached it or not.
        pred[dest] = no_vertex;

        // Clear other vertices. Optional?
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
            p_conv_t direct_conv = get_conv(from, to);

            if (direct_conv == nullptr)
                ;//cout << "No conv chain from " << from.description() << " to " << to.description() << " and no direct conv." << endl;
            else
                cout << "No conv chain from " << from.description() << " to " << to.description() << " but a direct conversion exists." << endl;

            //print_graph();

            conv_cache[key] = std::move(p_chain_t());
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

    //cout << "Conversion chain from " << from.description() << " to " << to.description() << " is ";
    //print_conv_chain(conv_cache[key]);

    return conv_cache[key];
}

}
