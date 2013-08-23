
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

template <typename T>
LM::ArgList make_arg_list(T value)
{
    LM::ExprPtr term = LM::Term<T>::create(value);
    LM::ArgList arg_list;
    arg_list.push_back(term);
    return arg_list;
}

template <typename T, typename U>
LM::ArgList make_arg_list(T value, U other_value)
{
    LM::ExprPtr term = LM::Term<T>::create(value);
    LM::ExprPtr other_term = LM::Term<T>::create(other_value);
    LM::ArgList arg_list;
    arg_list.push_back(term);
    arg_list.push_back(other_term);
    return arg_list;
}

template <typename T>
LM::TypeInfoList make_type_list()
{
    LM::TypeIndex type_index
        = LM::TypId<T>::get();
    LM::TypeInfoList arg_types;
    arg_types.push_back(type_index);
    return arg_types;
}

template <typename T, typename U>
LM::TypeInfoList make_type_list()
{
    LM::TypeIndex type_index
        = LM::TypId<T>::get();
    LM::TypeIndex other_type_index
        = LM::TypId<U>::get();
    LM::TypeInfoList arg_types;
    arg_types.push_back(type_index);
    arg_types.push_back(other_type_index);
    return arg_types;
}

template <typename T>
LM::TypeIndex get_type_index()
{
    return LM::TypId<T>::get();
}
