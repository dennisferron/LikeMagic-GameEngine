
#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

template <typename T>
LikeMagic::SFMO::ArgList make_arg_list(T value)
{
    LikeMagic::SFMO::ExprPtr term = LikeMagic::SFMO::Term<T, true>::create(value);
    LikeMagic::SFMO::ArgList arg_list;
    arg_list.push_back(term);
    return arg_list;
}

template <typename T>
LikeMagic::Utility::TypeInfoList make_type_list()
{
    LikeMagic::Utility::TypeIndex type_index
        = LikeMagic::Utility::BetterTypeInfo::create_index<T>();
    LikeMagic::Utility::TypeInfoList arg_types;
    arg_types.push_back(type_index);
    return arg_types;
}

