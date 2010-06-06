#include "LikeMagic/TypeConv/TypeConvGraph.hpp"

namespace LikeMagic { namespace TypeConv {

void TypeConvGraph::add_conv(BetterTypeInfo from, BetterTypeInfo to, AbstractTypeConverter const* conv)
{
    add_type(from);
    add_type(to);
    add_edge(indexes[from], indexes[to], graph).second.conv = conv;
}


ExprPtr TypeConvGraph::wrap_expr(ExprPtr from, BetterTypeInfo from, BetterTypeInfo to) const
{
}

}}
