#pragma once

#include "../Utility/StripModifiers.hpp"

#include "AbstractCallTargetSelector.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "../SFMO/MethodCall.hpp"
#include "../SFMO/CppObjProxy.hpp"

#include "ICustomField.hpp"

#include "boost/shared_ptr.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename CallAs, typename FieldAccessor>
class CustomFieldSetterTarget : public AbstractCallTargetSelector
{
private:
    typedef typename StripModifiers<CallAs>::strip stripped;
    typedef typename stripped::type ObjType;
    FieldAccessor f;
    typedef typename boost::remove_pointer<FieldAccessor>::type::FieldType FieldType;
    AbstractTypeSystem const& type_system;

public:

    static bool const is_const_func = false;

    CustomFieldSetterTarget(FieldAccessor f_, AbstractTypeSystem const& type_system_) : f(f_), type_system(type_system_) {}

    // Both the set and get target have a pointer to the same field accessor object;
    // only one of them needs to delete the shared accessor.
    ~CustomFieldSetterTarget() { delete f; }

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        f->set(
            type_system.try_conv<CallAs>(proxy->get_expr())->eval(),
            type_system.try_conv<FieldType>(args[0])->eval()
        );
        return 0;
    }

    virtual std::vector<BetterTypeInfo> get_arg_types() const
    {
        return make_arg_list(TypePack<FieldType>());
    }

};

}}
