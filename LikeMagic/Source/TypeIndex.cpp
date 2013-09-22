#include "LikeMagic/Utility/TypeIndex.hpp"
#include "LikeMagic/Utility/TypeInfoCache.hpp"
#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

using namespace LM;

TypeInfoPtr TypeIndex::get_info() const
{
    return TypeInfoCache::get_instance()->get_info(*this);
}

std::string TypeIndex::description() const
{
    std::stringstream result;
    result << get_info()->description() << " ";
    result << " " << get_id();
    result << "/" << get_class_id();
    return result.str();
}

TypeIndex TypeIndex::as_ptr_type() const
{
    return get_info()->as_ptr()->get_index();
}

TypeIndex TypeIndex::as_const_ptr_type() const
{
    return get_info()->as_const()->as_ptr()->get_index();
}
