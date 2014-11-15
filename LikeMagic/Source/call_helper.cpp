#include "LikeMagic/Exprs/call_helper.hpp"
#include "LikeMagic/Mirrors/TypeMirror.hpp"
#include "LikeMagic/Mirrors/CallTarget.hpp"
#include "LikeMagic/TypeSystem.hpp"

namespace LM {

ExprPtr call(ExprPtr expr, std::string name, ExprPtr args[], int size)
{
    TypeMirror* type_mirror = type_system->get_class(expr->get_type());
    auto* method = type_mirror->get_method(name, size);

    if (!method)
    {
        // Don't pass on to IoObject_perform if the problem is just wrong number of args;
        // use suggest method to give a good error message instead.
        if (type_mirror->has_method_named(name))
            type_mirror->suggest_method(name, size);
        else
            throw std::logic_error("Method " + name + " not found in type " + type_mirror->description());
    }

    return method->call(expr, args);
}

}
