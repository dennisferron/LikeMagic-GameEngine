#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"
#include "LikeMagic/Utility/TypeInfo.hpp"

namespace LM {

const TypeInfoList empty_arg_list_obj;
LIKEMAGIC_API const TypeInfoList& empty_arg_list = empty_arg_list_obj;

LIKEMAGIC_API TypeIndex const& get_index(TypeInfo const& type)
{
    return type_info_cache_instance->get_index(type, type.class_type());
}

LIKEMAGIC_API TypeInfo get_info(TypeIndex const& index)
{
    return type_info_cache_instance->get_info(index);
}

}
