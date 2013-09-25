// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Mirrors/TypeMirror.hpp"

#include <stdexcept>

#include <iostream>
using namespace std;

namespace LM {

void intrusive_ptr_add_ref(Expr* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(Expr* p)
{
    if (!--(p->ref_count))
        delete p;
}

Expr::~Expr()
{
    //std::cout << "~Expr " << this << std::endl;
    if (ref_count)
    {
        std::cout << "Fatal error:  Deleting abstract expression when ref_count is nonzero: ref_count = " << ref_count << std::endl;
        std::terminate();
    }

    if (get_auto_delete_ptr())
    {
        TypeIndex class_type = this->get_type().class_type();
        TypeMirror const* type_mirror = type_system->get_class(class_type);

        if (type_mirror == nullptr)
            throw std::logic_error("Cannot delete term or expr because no class found for " + class_type.description());

        type_mirror->try_delete(this);
    }
}

Expr::Expr(ValuePtr ptr, TypeIndex type_)
    : value_ptr(ptr), type(type_), ref_count(0),
        disable_to_script(false), auto_delete_ptr(false)
{
}

ValuePtr Expr::get_value_ptr() const
{
    return value_ptr;
}

void Expr::mark() const
{
    if (EvalAs<IMarkable const*>::has_conv(this))
    {
        ExprPtr warden;
        EvalAs<IMarkable const*>::value(const_cast<Expr*>(this), warden)->mark();
    }
}

bool Expr::get_auto_delete_ptr() const
{
    return auto_delete_ptr;
}

std::string Expr::description() const
{
    return "Expression<" + get_type().description() + ">";
}

void Expr::set_disable_to_script(bool value_)
{
    disable_to_script = value_;
}

void Expr::set_auto_delete_ptr(bool value_)
{
    auto_delete_ptr = value_;
}

bool Expr::disable_to_script_conv() const
{
    return disable_to_script;
}

bool Expr::is_terminal() const
{
    return true;
}

TypeIndex Expr::get_type() const
{
    return type;
}

}
