#include "LikeMagic/Exprs/BottomPtrExpr.hpp"
#include "LikeMagic/TypeSystem.hpp"

using namespace LM;

BottomPtrExpr::BottomPtrExpr(ExprPtr inner_) : inner(inner_) {}

ExprPtr BottomPtrExpr::create(ExprPtr inner) { return new BottomPtrExpr(inner); }

BottomPtrType BottomPtrExpr::eval()
{
    return reinterpret_cast<BottomPtrType>(
        LM::try_conv<void*>(inner)->eval());
}

bool BottomPtrExpr::is_terminal() const { return inner->is_terminal(); }

std::string BottomPtrExpr::description() const
{
    return std::string("any_ptr_type");
}

void BottomPtrExpr::mark() const { inner->mark(); }

// Since char* is convertible to IoSeq (string in Io) and we are convertible to any pointer,
// we would be convertible to IoSeq.  Not good.  Disable to-script conversions to prevent this:
bool BottomPtrExpr::disable_to_script_conv() const
{
    return true;
}
