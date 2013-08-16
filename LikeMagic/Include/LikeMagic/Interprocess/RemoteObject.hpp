#pragma once

#include "AbstractCppObjProxy.hpp"

namespace LikeMagic { namespace Interprocess

using TypeIndex = LikeMagic::Utility::TypeIndex;

struct ProcessControlStructure;
typedef int ObjectHandle;

class RemoteObject : public AbstractCppObjProxy
{
private:
    ProcessControlStructure* remote_process;
    ObjectHandle remote_object;

    RemoteObject(TypeIndex class_id, ProcessControlStructure* remote_process_);

    virtual ~ExprProxy();

public:

    static AbstractCppObjProxy* create(ExprPtr expr_);
    static AbstractCppObjProxy* create(ExprPtr expr_, LikeMagic::Utility::TypeIndex class_id);

    virtual void dispose() const;
    virtual boost::intrusive_ptr<AbstractExpression> get_expr();
    virtual bool is_terminal() const;
    virtual std::string description() const;
    virtual bool disable_to_script_conv() const;
    virtual void mark() const;
    virtual TypeIndex get_type() const;
};

}}
