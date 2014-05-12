#include "LikeMagic/CallTargets/ExprTarget.hpp"

using namespace LM;

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

TypeIndex ExprTarget::get_return_type() const
{
    return expr->get_type();
}

namespace LM {
LIKEMAGIC_API CallTarget* create_expr_target(ExprPtr expr)
{
    return new ExprTarget(expr);
}
}
