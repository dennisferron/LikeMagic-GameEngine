// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/MarkableObjGraph.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"

#include <stdexcept>

#include "boost/preprocessor/control/iif.hpp"
#include "boost/preprocessor/seq/for_each.hpp"
#include "boost/preprocessor/seq/for_each_i.hpp"

#define TypedArgList(r, data, i, elem) BOOST_PP_COMMA_IF(i) elem data##i

// Example:  ScriptFunc(0, MyRetType, FuncName, const, 3, ClassX, ClassY, ClassZ)
// Expands to: IoBlock On##FuncName; MyRetType FuncName(ClassX arg0, ClassY arg1, ClassZ arg2) const { ... }
//
// TODO:  Find way to implement calling of default implementation or "BASE" without adding
// undue burden on implementors who do not need/use base classes with default implementations.
//
#define ScriptFunc(IsVoid, RType, FuncName, CONST, ArgTypes) \
Iocaste::LMAdapters::IoBlock On##FuncName; \
virtual RType FuncName( \
    BOOST_PP_SEQ_FOR_EACH_I(TypedArgList, arg, ArgTypes) \
) CONST \
{ \
    if (On##FuncName.empty()) \
        /* BOOST_PP_IIF(IsVoid, , return) Base::FuncName(BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ArgTypes), arg));  */ \
        throw std::logic_error("No script block registered for " #FuncName); \
    else \
        BOOST_PP_IIF(IsVoid, , return) On##FuncName.eval<RType>(BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ArgTypes), arg)); \
}
