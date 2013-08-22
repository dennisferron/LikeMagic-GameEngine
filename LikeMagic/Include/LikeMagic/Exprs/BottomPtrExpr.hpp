// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "LikeMagic/Exprs/Expression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"

namespace LM {

// In formal type theory it is often convenient to define a type that is a superclass
// of all other types.  By convention it is called "Top" in type theory discussions,
// but in languages like Java or C# it is called "Object".  Anything
// can be implicitly converted to Object.

// What's the inverse concept?  It would be a type that 'inherits' from
// all other types.  This is the "Bottom" type in formal type theory.

// Although I know of no mainstream statically typed programming language that
// includes a "Bottom" type, in LikeMagic the Bottom type has a very useful
// purpose:  it enables you to cast pointers (such as void*) to other pointer types.
// It is basically a reinterpret_cast of a pointer, with the added convenience
// that you don't actually have to specify the type you're casting to.
// LikeMagic already knows the type of the function parameter into which you pass
// the bottom pointer, so you don't need to repeat this type declaration in script.
// For example in C++ you would do this:
//  void f(A* a); B* b;  ...  f((A*) b);
// But in Io with LikeMagic you only need to do this:
//   f(b as_any_ptr_type)

// Interestingly, although C++ has no formal concept of a Bottom type,
// the semantics of NULL act like a Bottom type in that you can
// assign NULL to any pointer.  And indeed the correspondence is close enough
// that I do use the LikeMagic Bottom pointer type to map script Nils to C++ NULLs.

struct BottomPtrTag__ {};
typedef BottomPtrTag__* BottomPtrType;

// This type can be converted to any other pointer in TypeConvGraph.
class BottomPtrExpr : public Expression<BottomPtrType>
{
private:
    ExprPtr inner;
    BottomPtrExpr(ExprPtr inner_);

public:

    static ExprPtr create(ExprPtr inner);
    inline virtual BottomPtrType eval();
    virtual bool is_terminal() const;
    virtual std::string description() const;
    virtual void mark() const;

    // Since char* is convertible to IoSeq (string in Io) and we are convertible to any pointer,
    // we would be convertible to IoSeq.  Not good.  Disable to-script conversions to prevent this:
    virtual bool disable_to_script_conv() const;
};

}
