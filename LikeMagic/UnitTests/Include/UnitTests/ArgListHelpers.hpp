
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

template <typename T, typename U>
LikeMagic::SFMO::ArgList make_arg_list(T value, U other_value)
{
    LikeMagic::SFMO::ExprPtr term = LikeMagic::SFMO::Term<T, true>::create(value);
    LikeMagic::SFMO::ExprPtr other_term = LikeMagic::SFMO::Term<T, true>::create(other_value);
    LikeMagic::SFMO::ArgList arg_list;
    arg_list.push_back(term);
    arg_list.push_back(other_term);
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

template <typename T, typename U>
LikeMagic::Utility::TypeInfoList make_type_list()
{
    LikeMagic::Utility::TypeIndex type_index
        = LikeMagic::Utility::BetterTypeInfo::create_index<T>();
    LikeMagic::Utility::TypeIndex other_type_index
        = LikeMagic::Utility::BetterTypeInfo::create_index<U>();
    LikeMagic::Utility::TypeInfoList arg_types;
    arg_types.push_back(type_index);
    arg_types.push_back(other_type_index);
    return arg_types;
}

template <typename T>
LikeMagic::Utility::TypeIndex get_type_index()
{
    return LikeMagic::Utility::BetterTypeInfo::create_index<T>();
}
