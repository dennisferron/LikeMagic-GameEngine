#include "LikeMagic/Exprs/ExprTrackingInfo.hpp"
#include "LikeMagic/Exprs/Expr.hpp"

#include "boost/unordered_map.hpp"

#include <sstream>

using namespace LM;
using namespace std;

ExprTrackingInfo::ExprTrackingInfo()
    : expr(nullptr), data(nullptr), name("no name") {}

ExprTrackingInfo::ExprTrackingInfo(Expr* const expr_)
    : expr(expr_), data(expr_->get_value_ptr().as_const), name("no name") {}

ExprTrackingInfo::ExprTrackingInfo(Expr* const expr_, std::string name_)
    : expr(expr_), data(expr_->get_value_ptr().as_const), name(name_) {}

ExprTrackingInfo::ExprTrackingInfo(ExprTrackingInfo const& that)
    : expr(that.expr), data(that.data), name(that.name)
{
}

ExprTrackingInfo& ExprTrackingInfo::operator =(ExprTrackingInfo const& that)
{
    expr = that.expr;
    data = that.data;
    name = that.name;
    return *this;
}

boost::unordered_map<Expr*, ExprTrackingInfo> expr_tracking;

namespace LM
{
    void track_expr(Expr* ptr)
    {
        // Uncomment for debugging
        //expr_tracking[ptr] = ExprTrackingInfo(ptr);
    }

    LIKEMAGIC_API void assert_expr(Expr* ptr)
    {
        /* Uncomment for debugging
        if (ptr == nullptr)
            throw std::runtime_error("Expr* is null");

        if (expr_tracking.find(ptr) == expr_tracking.end())
        {
            stringstream ss;
            ss << "No tracking info for expr "
                << ptr << endl;
            cout << ss.str() << endl;
            throw std::runtime_error(ss.str());
        }
        */
    }
}
