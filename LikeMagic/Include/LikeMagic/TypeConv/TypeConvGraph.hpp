// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include <utility> // std::pair
#include <map>
#include <bitset>

#include "boost/graph/graph_traits.hpp"
#include "boost/graph/adjacency_list.hpp"

#include "boost/unordered_map.hpp"

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"
#include "LikeMagic/Exprs/Expr.hpp"

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Utility/KeyWrapper.hpp"

namespace LM {

using namespace boost::graph;
using LM::TypeIndex;
using LM::TypeIndex;
using LM::TypeInfoList;

struct FindType;

class TypeConvGraph
{
private:
    // To give it acess to our private typedefs.
    friend struct FindType;

    typedef boost::intrusive_ptr<AbstractTypeConverter const> p_conv_t;
    typedef boost::shared_ptr<std::vector<p_conv_t>> p_chain_t;

    struct edge_info
    {
        p_conv_t conv;
        float cost;
    };

    struct vertex_info
    {
        TypeIndex type;
    };

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, vertex_info, edge_info> graph_t;
    typedef boost::graph_traits<graph_t>::vertex_descriptor vertex_t;
    typedef boost::graph_traits<graph_t>::edge_descriptor edge_t;
    typedef std::vector<vertex_t> vertex_map_t;

    graph_t graph;
    vertex_map_t vertex_map;
    std::vector<bool> has_vertex;

    // Mutable is for when the object is logically const, but technically a member needs
    // to sometimes change in a way that's not visible from outside the class.
    // Caching is a perfect example of this.
    mutable boost::unordered_map<std::pair<TypeIndex, TypeIndex>, p_chain_t> conv_cache;

    bool has_type(TypeIndex type) const;

    ExprPtr build_conv_chain(ExprPtr from_expr, p_chain_t const& chain) const;
    p_chain_t const& search_for_conv(TypeIndex from, TypeIndex to) const;

    // Don't allow TypeConvGraph to be copied accidently.
    TypeConvGraph(TypeConvGraph const&)=delete;
    TypeConvGraph& operator =(TypeConvGraph const&)=delete;

    vertex_t const no_vertex;

    p_conv_t bot_conv;

public:
    TypeConvGraph();
    ~TypeConvGraph();
    vertex_t  add_type(TypeIndex type);
    void add_conv(TypeIndex from, TypeIndex to, p_conv_t conv);
    ExprPtr wrap_expr(ExprPtr from_expr, TypeIndex from, TypeIndex to) const;
    bool has_conv(TypeIndex from_type, TypeIndex to_type) const;
    void print_graph() const;
    void print_conv_chain(TypeIndex from, TypeIndex to) const;
    void print_conv_chain(p_chain_t const& chain) const;
};

}
