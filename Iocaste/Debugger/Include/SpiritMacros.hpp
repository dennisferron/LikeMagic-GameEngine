
// Do NOT define #pragma once in rules headers.

#if defined(QI_DEFN) || defined(KARMA_DEFN)
    #if defined(QI_DECL) || defined(QI_EXTERN)
        #error "Cannot do a QI_DECL and a *_DEFN in the same place."
    #endif
    #if defined(KARMA_DECL) || defined(KARMA_EXTERN)
        #error "Cannot do a KARMA_DECL and a *_DEFN in the same place."
    #endif
    #if defined(DECL_STRUCTS)
        #error "Cannot do a DECL_STRUCTS and a *_DEFN in the same place."
    #endif
#endif

#if defined(QI_DECL) && defined(QI_EXTERN)
    #error "QI_DECL and QI_EXTERN are both defined; you must define only one (undef the mode you aren't using)."
#endif

#if defined(KARMA_DECL) && defined(KARMA_EXTERN)
    #error "KARMA_DECL and KARMA_EXTERN are both defined; you must define only one (undef the mode you aren't using)."
#endif

#if defined(QI_DECL) || defined(KARMA_DECL) || defined(QI_EXTERN) || defined(KARMA_EXTERN)
#include "boost/spirit/include/phoenix_core.hpp"
#include "boost/spirit/include/phoenix_operator.hpp"
#include "boost/spirit/include/phoenix_object.hpp"
#include "boost/fusion/include/adapt_struct.hpp"
#include "boost/fusion/include/io.hpp"
#endif

#if defined(QI_DECL) || defined(QI_EXTERN)
#include "boost/spirit/include/qi.hpp"
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
typedef std::string::const_iterator Iterator;
#endif

#if defined(KARMA_DECL) || defined(KARMA_EXTERN)
#include "boost/spirit/include/karma.hpp"
namespace karma = boost::spirit::karma;
namespace ascii = boost::spirit::ascii;
typedef std::back_insert_iterator<std::string> OutputIterator;
#endif

#if defined(DECL_STRUCTS)
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/seq/for_each.hpp"
#endif

#undef DEFN_QI_RULE
#undef DECL_QI_RULE
#undef DECL_QI_SYMBOLS
#undef DEFN_KARMA_RULE
#undef DECL_KARMA_RULE
#undef DECL_KARMA_SYMBOLS
#undef SPIRIT_RULE
#undef SPIRIT_SYMBOLS
#undef SPIRIT_FUSION_IMPL
#undef DEFINE_STRUCT
#undef WITHIN_NAMESPACE

#if defined(QI_DECL)
    #define DECL_QI_RULE(NAMESPACE_SEQ, rtype, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(qi_rules), qi::rule<Iterator, rtype()> rule_name; )
    #define DECL_QI_SYMBOLS(NAMESPACE_SEQ, Char, T, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(qi_rules), qi::symbols<Char, T> rule_name; )
#elif defined(QI_EXTERN)
    #define DECL_QI_RULE(NAMESPACE_SEQ, rtype, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(qi_rules), extern qi::rule<Iterator, rtype()> rule_name; )
    #define DECL_QI_SYMBOLS(NAMESPACE_SEQ, Char, T, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(qi_rules), extern qi::symbols<Char, T> rule_name; )
#else
    #define DECL_QI_RULE(NAMESPACE_SEQ, rtype, rule_name)
    #define DECL_QI_SYMBOLS(NAMESPACE_SEQ, Char, T, rule_name)
#endif

#ifdef QI_DEFN
    #define DEFN_QI_RULE(rule_expr) rule_expr;
#else
    #define DEFN_QI_RULE(rule_expr)
#endif

#if defined(KARMA_DECL)
    #define DECL_KARMA_RULE(NAMESPACE_SEQ, rtype, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(karma_rules), karma::rule<OutputIterator, rtype()> rule_name; )
    #define DECL_KARMA_SYMBOLS(NAMESPACE_SEQ, Char, T, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(karma_rules), karma::symbols<Char, T> rule_name; )
#elif defined(KARMA_EXTERN)
    #define DECL_KARMA_RULE(NAMESPACE_SEQ, rtype, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(karma_rules), extern karma::rule<OutputIterator, rtype()> rule_name; )
    #define DECL_KARMA_SYMBOLS(NAMESPACE_SEQ, Char, T, rule_name) WITHIN_NAMESPACE(NAMESPACE_SEQ(karma_rules), extern karma::symbols<Char, T> rule_name; )
#else
    #define DECL_KARMA_RULE(NAMESPACE_SEQ, rtype, rule_name)
    #define DECL_KARMA_SYMBOLS(NAMESPACE_SEQ, Char, T, rule_name)
#endif

#ifdef KARMA_DEFN
    #define DEFN_KARMA_RULE(rule_expr) rule_expr;
#else
    #define DEFN_KARMA_RULE(rule_expr)
#endif

#if defined(QI_DECL) || defined(KARMA_DECL) || defined(QI_DEFN) || defined(KARMA_DEFN) || defined(QI_EXTERN) || defined(KARMA_EXTERN)
    #define SPIRIT_RULE(NAMESPACE_SEQ, RTYPE, RULE_NAME, QI_EXPR, KARMA_EXPR) \
        DECL_QI_RULE(NAMESPACE_SEQ, RTYPE, RULE_NAME) \
        DEFN_QI_RULE(RULE_NAME = QI_EXPR) \
        DECL_KARMA_RULE(NAMESPACE_SEQ, RTYPE, RULE_NAME) \
        DEFN_KARMA_RULE(RULE_NAME = KARMA_EXPR)
#else
    #define SPIRIT_RULE(NAMESPACE_SEQ, RTYPE, RULE_NAME, QI_EXPR, KARMA_EXPR)
#endif

#if defined(QI_DECL) || defined(KARMA_DECL) || defined(QI_DEFN) || defined(KARMA_DEFN) || defined(QI_EXTERN) || defined(KARMA_EXTERN)
    #define SPIRIT_SYMBOLS(NAMESPACE_SEQ, RULE_NAME, QI_EXPR, KARMA_EXPR) \
        DECL_QI_SYMBOLS(NAMESPACE_SEQ, char const, char const, RULE_NAME) \
        DEFN_QI_RULE(QI_EXPR) \
        DECL_KARMA_SYMBOLS(NAMESPACE_SEQ, char, char const*, RULE_NAME) \
        DEFN_KARMA_RULE(KARMA_EXPR)
#else
    #define SPIRIT_SYMBOLS(NAMESPACE_SEQ, RULE_NAME, QI_EXPR, KARMA_EXPR)
#endif

#if defined(QI_DECL) || defined(KARMA_DECL) || defined(QI_EXTERN) || defined(KARMA_EXTERN)
    #define SPIRIT_FUSION_IMPL(NAME, ATTRIBUTES) BOOST_FUSION_ADAPT_STRUCT(NAME, ATTRIBUTES)
#else
    #define SPIRIT_FUSION_IMPL(NAME, ATTRIBUTES)
#endif

#ifdef DECL_STRUCTS
#define SPIRIT_STRUCT_ELEM(r, data, elem) V_BOOST_PP_TUPLE_ELEM(0, elem) V_BOOST_PP_TUPLE_ELEM(1, elem);

#define ADD_PAREN_1(A, B) ((A, B)) ADD_PAREN_2
#define ADD_PAREN_2(A, B) ((A, B)) ADD_PAREN_1
#define ADD_PAREN_1_END
#define ADD_PAREN_2_END
#define ADD_PARENS(INPUT) BOOST_PP_CAT(ADD_PAREN_1 INPUT,_END)

#define DEFINE_STRUCT_IMPL(struct_name, fields)          \
    struct struct_name {                                 \
       BOOST_PP_SEQ_FOR_EACH(DEFINE_FIELD, ~, fields)    \
    };

#define DEFINE_FIELD(r, data, field_tuple)  \
        BOOST_PP_TUPLE_ELEM(2, 0, field_tuple) BOOST_PP_TUPLE_ELEM(2, 1, field_tuple);

#define DEFINE_STRUCT(NAMESPACE_SEQ, struct_name, fields)                    \
    WITHIN_NAMESPACE(NAMESPACE_SEQ, \
     DEFINE_STRUCT_IMPL(struct_name,       \
        BOOST_PP_CAT(ADD_PAREN_1 fields,_END)))
#else
#define DEFINE_STRUCT(NAMESPACE_SEQ, struct_name, fields)
#endif

#define START_NAMESPACE(r, data, elem) namespace elem {
#define END_NAMESPACE(r, data, elem) }

#if defined(QI_DEFN) || defined(KARMA_DEFN)
#define WITHIN_NAMESPACE(NAMESPACE_SEQ, ...) $$$CANNOT_DECLARE_NAMESPACE_HERE$$$
#else
#define WITHIN_NAMESPACE(NAMESPACE_SEQ, ...) \
    BOOST_PP_SEQ_FOR_EACH(START_NAMESPACE, ~, NAMESPACE_SEQ) \
        __VA_ARGS__ \
    BOOST_PP_SEQ_FOR_EACH(END_NAMESPACE, ~, NAMESPACE_SEQ)
#endif

#define PREPEND_NAMESPACE_IMPL(r, data, elem) elem::
#define PREPEND_NAMESPACE(NAMESPACE_SEQ, TYPE_NAME) BOOST_PP_SEQ_FOR_EACH(PREPEND_NAMESPACE_IMPL, ~, NAMESPACE_SEQ)TYPE_NAME

#define SPIRIT_STRUCT(NAMESPACE_SEQ, STRUCT_NAME, ATTRIBUTES, RULE_NAME, QI_EXPR, KARMA_EXPR) \
    DEFINE_STRUCT(NAMESPACE_SEQ, STRUCT_NAME, ATTRIBUTES) \
    SPIRIT_FUSION_IMPL(PREPEND_NAMESPACE(NAMESPACE_SEQ, STRUCT_NAME), ATTRIBUTES) \
    SPIRIT_RULE(NAMESPACE_SEQ, STRUCT_NAME, RULE_NAME, QI_EXPR, KARMA_EXPR)
