#pragma once

#include "Rules/RuleStructs.hpp"

namespace IoDbg { namespace Rules {

struct GdbResponse
{
    std::vector<GdbResponseType> values;
    boost::optional<std::string> prompt;

    void pushActionable(GdbActionableType t)
    {
        values.push_back(GdbActionable {t});
    }
};

template <typename Visitor>
GdbResponseType visitIfActionable(Visitor& v, GdbResponseType t)
{
    if (auto a = boost::get<GdbActionable>(&t))
        return {boost::apply_visitor(v, a->value)};
    else
        return t;
}

template <typename Visitor>
void visitAll(Visitor& v, GdbResponseType t)
{
    if (auto a = boost::get<GdbActionable>(&t))
        boost::apply_visitor(v, a->value);
    else if (auto u = boost::get<GdbUnactionable>(&t))
        boost::apply_visitor(v, u->value);
    else if (auto c = boost::get<GdbContextSensitive>(&t))
        boost::apply_visitor(v, c->value);
    //else
    //    raiseError(LogicError("Unhandled response type"));
}

template <typename T>
T* getActionable(GdbResponseType* r)
{
    if (auto a = boost::get<GdbActionable>(r))
        if (auto t = boost::get<T>(&(a->value)))
            return t;
    return NULL;
}

template <typename T>
bool hasActionable(std::vector<GdbResponseType> items)
{
    for (auto line_item : items)
        if (getActionable<T>(&line_item))
            return true;

    return false;
}

}}
