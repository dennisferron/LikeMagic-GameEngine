// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/TypeConv/ConvertibleTo.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

#include "boost/intrusive_ptr.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <set>
#include <vector>

// forward declarations
namespace LikeMagic { namespace TypeConv {

class AbstractTypeConverter;

}}

namespace LikeMagic { namespace SFMO {

using LikeMagic::Utility::BetterTypeInfo;

// more forward declarations
class AbstractObjectSet;

class AbstractExpression;

void intrusive_ptr_add_ref(AbstractExpression* p);
void intrusive_ptr_release(AbstractExpression* p);


template <typename To>
class Expression;

class AbstractExpression : public LikeMagic::IMarkable
{
private:
    int ref_count;

    friend void intrusive_ptr_add_ref(AbstractExpression* p);
    friend void intrusive_ptr_release(AbstractExpression* p);

protected:

    virtual ~AbstractExpression()
    {
        //std::cout << "~AbstractExpression " << this << std::endl;
        if (ref_count)
        {
            std::cout << "Fatal error:  Deleting abstract expression when ref_count is nonzero: ref_count = " << ref_count << std::endl;
            std::terminate();
        }
    }

    AbstractExpression() : ref_count(0) {}

public:

    virtual std::set<AbstractObjectSet*> get_objsets() { return std::set<AbstractObjectSet*>(); }
    virtual bool is_terminal() const = 0;
    virtual bool is_lazy() const = 0;
    virtual BetterTypeInfo get_type() const = 0;
    virtual std::string description() const = 0;

    // Compares the expression contents to the other expression's contents.
    // It can't be const because it may cause an eval().
    // Important:  Use AbstractTypeSystem::try_conv to convert the other expression to this type.
    // The result of calling equals if ExprPtr other isn't really of a compatible
    // type to this expression is undefined.
    virtual bool equals(ExprPtr other);
};

// Most of the time you will be using an expression via smart ptr.
typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;

// Sometimes you put expressions together into arg lists, esp. for functionoid.
typedef std::vector<ExprPtr> ArgList;



}}
