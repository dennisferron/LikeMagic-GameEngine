// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/TypeConv/ConvertibleTo.hpp"
#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

#include "boost/intrusive_ptr.hpp"

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <set>
#include <vector>

// forward declarations
namespace LM {

class AbstractTypeConverter;

}

namespace LM {

using LM::TypeIndex;

class AbstractExpression;

void intrusive_ptr_add_ref(AbstractExpression* p);
void intrusive_ptr_release(AbstractExpression* p);

class AbstractExpression : public LM::IMarkable
{
private:
    int ref_count;

    friend void intrusive_ptr_add_ref(AbstractExpression* p);
    friend void intrusive_ptr_release(AbstractExpression* p);

    bool disable_to_script;
    bool auto_delete_ptr;

protected:

    virtual ~AbstractExpression();
    AbstractExpression();

public:

    virtual std::string description() const;

    virtual TypeIndex get_type() const = 0;
    virtual TypeIndex get_class_type() const;

    virtual bool is_terminal() const;
    virtual bool is_null() const;

    virtual bool disable_to_script_conv() const;
    virtual void set_disable_to_script(bool value);

    virtual void set_auto_delete_ptr(bool value);
    virtual bool get_auto_delete_ptr() const;
};

// Most of the time you will be using an expression via smart ptr.
typedef boost::intrusive_ptr<AbstractExpression> ExprPtr;

// Sometimes you put expressions together into arg lists, esp. for functionoid.
typedef std::vector<ExprPtr> ArgList;



}
