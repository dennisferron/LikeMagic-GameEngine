#pragma once

#include "AbstractCppObjProxy.hpp"

namespace LM { namespace Interprocess

using TypeIndex = LM::TypeIndex;

struct ProcessControlStructure;
typedef int ObjectHandle;

class RemoteObject : public AbstractCppObjProxy
{
private:
    ProcessControlStructure* remote_process;
    ObjectHandle remote_object;

    RemoteObject(TypeIndex class_id, ProcessControlStructure* remote_process_);

    virtual ~RemoteObject();

public:

    static ExprPtr create(ExprPtr expr_);
    static ExprPtr create(ExprPtr expr_, LM::TypeIndex class_id);

    virtual void dispose() const;
    virtual ExprPtr get_expr();
    virtual bool is_terminal() const;
    virtual std::string description() const;
    virtual bool disable_to_script_conv() const;
    virtual void mark() const;
    virtual TypeIndex get_type() const;
};

}
