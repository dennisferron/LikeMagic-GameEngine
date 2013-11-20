
#include "Rules/RuleStructs.hpp"
using namespace IoDbg::Rules;

#include "ParseGrammars.hpp"
#include "GdbResponseParser.hpp"
using namespace IoDbg;

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/karma.hpp>

#include <iostream>
#include <string>
#include <complex>
using namespace std;

#include <boost/algorithm/string.hpp>
#include "boost/algorithm/string/predicate.hpp"

#include <boost/spirit/home/phoenix/bind/bind_member_variable.hpp>
#include <boost/spirit/home/phoenix/scope/let.hpp>
#include <boost/spirit/home/phoenix/scope/local_variable.hpp>
#include <boost/spirit/home/phoenix/statement/if.hpp>
using namespace boost::phoenix::local_names;
namespace phx = boost::phoenix;

#include "Exception.hpp"

using namespace IoDbg;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

#include "StringUnescapeParser.hpp"

#define QI_DECL
#include "Rules/GdbValue.hpp"
#include "Rules/SharedTypes.hpp"
#undef QI_DECL

#define QI_EXTERN
#include "Rules/GdbBanner.hpp"
#undef QI_EXTERN

#define QI_DECL
#include "Rules/Unactionable.hpp"
#include "Rules/Actionable.hpp"
#undef QI_DECL

using namespace IoDbg::Rules;
using namespace IoDbg::Rules::qi_rules;

namespace Iocaste {
    namespace Debugger {

StringUnescapeParser<Iterator> unesc_grammar;


struct GdbResponseParseGrammar : qi::grammar<std::string::const_iterator, GdbResponseType()>
{
    typedef std::string::const_iterator Iterator;

    GdbResponseParseGrammar(bool use_alt_parser) :
        GdbResponseParseGrammar::base_type(use_alt_parser? alt_start : start),
            gdb_value(gdb_value_parse_grammar())
    {

        start = actionable | unactionable;
        alt_start = context_sens;
    }

    unique_ptr<qi::grammar<Iterator, Rules::GdbValue()>> gdb_value;
    qi::rule<Iterator, GdbResponseType()> start;
    qi::rule<Iterator, GdbResponseType()> alt_start;
};

boost::spirit::qi::grammar<std::string::const_iterator, GdbResponseType()>* response_parse_grammar(bool use_alt_parser)
{
    #define QI_DEFN
    #include "Rules/GdbValue.hpp"
    #include "Rules/SharedTypes.hpp"
    #include "Rules/Unactionable.hpp"
    #include "Rules/Actionable.hpp"
    return new GdbResponseParseGrammar(use_alt_parser);
}

    }
}

