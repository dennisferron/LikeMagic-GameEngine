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
#include "LikeMagic/Lang/LangBlock.hpp"

#include "LikeMagic/Utility/TraceDb.hpp"
using namespace LM;

#include <stdexcept>
#include <sstream>
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
    friend class ExprAllocator;

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
        // DLF COMMENT OUT FOR DEBUGGING
        delete this;
    }
}

ExprImpl::~ExprImpl()
{
    IF_TRACE_DB(trace_db->delete_Expr(this));

    //std::cout << "~Expr " << this << std::endl;
    if (ref_count)
    {
        std::cout << "Deleting abstract expression when ref_count is nonzero: ref_count = " << ref_count << std::endl;
    }

    if (get_auto_delete_ptr())
    {
        TypeMirror const* type_mirror = type_system->get_class(get_type());

        if (type_mirror == nullptr)
        {
            cout << "Cannot delete term or expr because no class found for " + get_type().description() << endl;

            // Don't throw from destructor
            return;
            //throw std::logic_error("Cannot delete term or expr because no class found for " + get_type().description());
        }

        //cout << "try_delete " << type_mirror->get_class_name() << endl;

        type_mirror->try_delete(this);
    }
}

void track_expr(Expr* ptr);

LIKEMAGIC_API Expr* create_expr(ValuePtr ptr_, TypeIndex type_)
{
    ExprImpl* result = new ExprImpl(ptr_, type_, nullptr);
    track_expr(result);
    return result;
}

LIKEMAGIC_API Expr* create_reference(ValuePtr ptr_, TypeIndex type_, ExprPtr storage_location_)
{
    ExprImpl* result = new ExprImpl(ptr_, type_, storage_location_);
    track_expr(result);
    return result;
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
    if (value_ptr.as_const != nullptr)
    {
        if (EvalAs<IMarkable const*>::has_conv(this))
        {
            cout << "About to mark " + this->description() << endl;

            ExprPtr ward;
            auto* ptr = EvalAs<IMarkable const*>::value(const_cast<ExprImpl*>(this), ward);
            if (ptr == nullptr)
            {
                cout << "When marking an IMarkable, value_ptr was not null but casted ptr was!" << endl;
            }
            else
            {
                ptr->mark();
            }
        }
    }

    TypeMirror const* type_mirror = type_system->get_class(get_type());

    if (type_mirror == nullptr)
    {
        cout << "Cannot mark term or expr because no class found for " + get_type().description() << endl;
        throw std::logic_error("Cannot mark term or expr because no class found for " + get_type().description());
    }

    type_mirror->mark();

    if (storage_location != nullptr)
        storage_location->mark();
}

bool ExprImpl::get_auto_delete_ptr() const
{
    return auto_delete_ptr;
}

std::string ExprImpl::description() const
{
    stringstream ss;
    ss << "Expr of " << get_type().description() << " (" << get_type().get_id() << ")";
    return ss.str();
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
