// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/AbstractTypeInfo.hpp"
#include "LikeMagic/Exprs/ValuePtr.hpp"
#include "boost/intrusive_ptr.hpp"

#include <vector>

namespace LM {

class Expr;

void intrusive_ptr_add_ref(Expr* p);
void intrusive_ptr_release(Expr* p);

class Expr : public LM::IMarkable
{
protected:
    ValuePtr value_ptr;
    TypeIndex type;

private:
    int ref_count;

    bool disable_to_script;
    bool auto_delete_ptr;

    friend void intrusive_ptr_add_ref(Expr* p);
    friend void intrusive_ptr_release(Expr* p);

protected:

    virtual ~Expr();

public:
    Expr(ValuePtr ptr_, TypeIndex type_);

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

// Most of the time you will be using an expression via smart ptr.
typedef boost::intrusive_ptr<Expr> ExprPtr;

// Sometimes you put expressions together into arg lists, esp. for functionoid.
typedef std::vector<ExprPtr> ArgList;

}
