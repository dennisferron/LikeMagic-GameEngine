#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"
#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

namespace LM {

const TypeInfoList empty_arg_list_obj;
LIKEMAGIC_API const TypeInfoList& empty_arg_list = empty_arg_list_obj;

LIKEMAGIC_API TypeIndex const& get_index(TypeInfoPtr type)
{
    return type_info_cache_instance->get_index(type, type->class_type());
}

LIKEMAGIC_API TypeInfoPtr get_info(TypeIndex const& index)
{
    return type_info_cache_instance->get_info(index);
}

}
