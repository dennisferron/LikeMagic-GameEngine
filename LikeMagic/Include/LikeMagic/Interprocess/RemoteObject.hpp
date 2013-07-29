#pragma once

#include "AbstractCppObjProxy.hpp"

namespace LikeMagic { namespace Interprocess

struct ProcessControlStructure;
typedef int ObjectHandle;

class RemoteObject : public AbstractCppObjProxy
{
private:
    ProcessControlStructure* remote_process;
    ObjectHandle remote_object;

    RemoteObject(AbstractTypeSystem const& type_system_, LikeMagic::Utility::TypeIndex class_id, ProcessControlStructure* remote_process_);

    virtual ~ExprProxy();

public:

    static AbstractCppObjProxy* create(ExprPtr expr_, AbstractTypeSystem const& type_system);
    static AbstractCppObjProxy* create(ExprPtr expr_, AbstractTypeSystem const& type_system, LikeMagic::Utility::TypeIndex class_id);

    virtual void dispose() const;
    virtual boost::intrusive_ptr<AbstractExpression> get_expr();
    virtual bool is_terminal() const;
    virtual std::string describe() const;
    virtual bool disable_to_script_conv() const;
    virtual void mark() const;
    virtual TypeIndex get_type() const;
};

}}
