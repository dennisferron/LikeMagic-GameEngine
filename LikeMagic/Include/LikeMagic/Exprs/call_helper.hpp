#include "LikeMagic/Exprs/Expr.hpp"

namespace LM {

LIKEMAGIC_API ExprPtr call(ExprPtr expr, std::string name, ExprPtr args[], int arg_count);
LIKEMAGIC_API ExprPtr call_static(TypeIndex type, std::string name, ExprPtr args[], int arg_count);

}
