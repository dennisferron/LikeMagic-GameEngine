// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Exprs/Expr.hpp"

#include <stdexcept>

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
        // TODO:  Get deleter from TypeSystem/TypeMirror, and then try_delete if auto delete pt..
        //TermDeleter<T const>::delete_if_possible((T*)value_ptr);
    }
}

Expr::Expr() : ref_count(0), disable_to_script(false), auto_delete_ptr(false), value_ptr(NULL)
{
}

Expr::Expr(void const* ptr) : ref_count(0), disable_to_script(false), auto_delete_ptr(false), value_ptr(ptr)
{
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
