#include "LikeMagic/CallTargets/ExprTarget.hpp"

using namespace LikeMagic::CallTargets;
using namespace LikeMagic::Exprs;

ExprTarget::ExprTarget(ExprPtr expr_)
    : expr(expr_)
{
}

ExprPtr ExprTarget::call(ExprPtr target, ArgList args) const
{
    return expr;
}

TypeInfoList const& ExprTarget::get_arg_types() const
{
    return empty_arg_list;
}
