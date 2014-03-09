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
#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Exprs/ValuePtr.hpp"

#include <vector>

namespace LM {

class Expr;

LIKEMAGIC_API void intrusive_ptr_add_ref(Expr* p);
LIKEMAGIC_API void intrusive_ptr_release(Expr* p);

class Expr : public IMarkable
{
protected:
    virtual void add_ref() = 0;
    virtual void release() = 0;
    friend LIKEMAGIC_API void intrusive_ptr_add_ref(Expr* p);
    friend LIKEMAGIC_API void intrusive_ptr_release(Expr* p);
    virtual ~Expr() = 0;

public:

    virtual std::string description() const = 0;
    virtual TypeIndex get_type() const = 0;
    virtual bool is_terminal() const = 0;
    virtual bool disable_to_script_conv() const = 0;
    virtual void set_disable_to_script(bool value) = 0;
    virtual void set_auto_delete_ptr(bool value) = 0;
    virtual bool get_auto_delete_ptr() const = 0;
    virtual ValuePtr get_value_ptr() const = 0;
    virtual void mark() const = 0;
};

inline Expr::~Expr() {}

typedef boost::intrusive_ptr<Expr> ExprPtr;
typedef ExprPtr ArgList[];

LIKEMAGIC_API Expr* create_expr(ValuePtr ptr_, TypeIndex type_);
LIKEMAGIC_API Expr* create_reference(ValuePtr ptr_, TypeIndex type_, ExprPtr storage_location_);

}
