// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "boost/shared_ptr.hpp"

#include "LikeMagic/Utility/TypeInfo.hpp"
#include "LikeMagic/Exprs/Expr.hpp"
#include "LikeMagic/Exprs/TermDeleter.hpp"

namespace LM {

class TypeSystem;
class Expr;
class CallTarget;

class TypeMirror
{
public:
    virtual ~TypeMirror() = 0;
    virtual std::string get_class_name() const = 0;
    virtual std::string description() const = 0;
    virtual CallTarget* get_method(std::string method_name, int num_args, bool in_base_class=false) const = 0;
    virtual void add_method(std::string method_name, CallTarget* method) = 0;
    virtual void add_base(TypeMirror const* base) = 0;
    virtual bool has_base(TypeMirror const* base) const = 0;
    virtual TypeIndex get_class_type() const = 0;
    virtual size_t get_instance_size() const = 0;
    virtual void suggest_method(std::string method_name, int num_args) const = 0;
    virtual void try_delete(Expr const* expr) const = 0;
    virtual void set_deleter(std::unique_ptr<AbstractTermDeleter const> deleter) = 0;
    virtual bool has_method_named(std::string method_name, bool in_base_class=false) const = 0;
};

inline TypeMirror::~TypeMirror() {}

LIKEMAGIC_API TypeMirror* create_type_mirror(std::string class_name, size_t instance_size, TypeIndex class_type);

}
