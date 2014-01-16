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

class Expr;

LIKEMAGIC_API void intrusive_ptr_add_ref(Expr* p);
LIKEMAGIC_API void intrusive_ptr_release(Expr* p);

class ExprImpl : private Expr
{
protected:
    int ref_count;

    ValuePtr value_ptr;
    TypeIndex type;

    ExprPtr storage_location;

    bool disable_to_script;
    bool auto_delete_ptr;

    friend LIKEMAGIC_API Expr* create_expr(ValuePtr ptr_, TypeIndex type_);
    friend LIKEMAGIC_API Expr* create_reference(ValuePtr ptr_, TypeIndex type_, ExprPtr storage_location_);

protected:

    virtual ~ExprImpl();
    virtual void add_ref();
    virtual void release();

public:
    ExprImpl(ValuePtr ptr_, TypeIndex type_, ExprPtr storage_location_);

    virtual std::string description() const;
    virtual TypeIndex get_type() const;
    virtual bool is_terminal() const;
    virtual bool disable_to_script_conv() const;
    virtual void set_disable_to_script(bool value);
    virtual void set_auto_delete_ptr(bool value);
    virtual bool get_auto_delete_ptr() const;
    virtual ValuePtr get_value_ptr() const;
    virtual void mark() const;
};

LIKEMAGIC_API void intrusive_ptr_add_ref(Expr* p)
{
    p->add_ref();
}

LIKEMAGIC_API void intrusive_ptr_release(Expr* p)
{
    p->release();
}

void ExprImpl::add_ref()
{
    ++ref_count;
}

void ExprImpl::release()
{
    if (!--ref_count)
    {
        delete this;
    }
}

ExprImpl::~ExprImpl()
{
    //std::cout << "~Expr " << this << std::endl;
    if (ref_count)
    {
        std::cout << "Deleting abstract expression when ref_count is nonzero: ref_count = " << ref_count << std::endl;
    }

    if (get_auto_delete_ptr())
    {
        TypeMirror const* type_mirror = type_system->get_class(get_type());

        if (type_mirror == nullptr)
            throw std::logic_error("Cannot delete term or expr because no class found for " + get_type().description());

        type_mirror->try_delete(this);
    }
}

LIKEMAGIC_API Expr* create_expr(ValuePtr ptr_, TypeIndex type_)
{
    ExprImpl* result = new ExprImpl(ptr_, type_, nullptr);
    // TODO: Remove this when done debugging.
    //cout << "Created expr " << result << " type " << type_.get_id() << " " << type_.description() << " value_ptr=" << result->value_ptr.as_const << endl;
    return result;
}

LIKEMAGIC_API Expr* create_reference(ValuePtr ptr_, TypeIndex type_, ExprPtr storage_location_)
{
    return new ExprImpl(ptr_, type_, storage_location_);
}

ExprImpl::ExprImpl(ValuePtr ptr_, TypeIndex type_, ExprPtr storage_location_)
    : ref_count(0), value_ptr(ptr_), type(type_), storage_location(storage_location_),
        disable_to_script(false), auto_delete_ptr(false)
{
}

ValuePtr ExprImpl::get_value_ptr() const
{
    return value_ptr;
}

void ExprImpl::mark() const
{
    if (value_ptr.as_const != nullptr && EvalAs<IMarkable const*>::has_conv(this))
    {
        ExprPtr ward;
        EvalAs<IMarkable const*>::value(const_cast<ExprImpl*>(this), ward)->mark();
    }

    // TODO:  Mark class members!

    if (storage_location != nullptr)
        storage_location->mark();
}

bool ExprImpl::get_auto_delete_ptr() const
{
    return auto_delete_ptr;
}

std::string ExprImpl::description() const
{
    return "Expression<" + get_type().description() + ">";
}

void ExprImpl::set_disable_to_script(bool value_)
{
    disable_to_script = value_;
}

void ExprImpl::set_auto_delete_ptr(bool value_)
{
    auto_delete_ptr = value_;
}

bool ExprImpl::disable_to_script_conv() const
{
    return disable_to_script;
}

bool ExprImpl::is_terminal() const
{
    return true;
}

TypeIndex ExprImpl::get_type() const
{
    return type;
}

}
