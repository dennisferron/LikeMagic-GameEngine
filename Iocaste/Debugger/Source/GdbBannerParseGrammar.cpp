
#include "ParseGrammars.hpp"
#include "GdbResponseParser.hpp"
using namespace Iocaste::Debugger;

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

using namespace Iocaste::Debugger;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

#include "GdbResponseFusion.hpp"
#include "StringUnescapeParser.hpp"

namespace Iocaste {
    namespace Debugger {

struct GdbBannerGrammar : qi::grammar<std::string::const_iterator, GdbResponses::Banner()>
{
    typedef std::string::const_iterator Iterator;

    GdbBannerGrammar() : GdbBannerGrammar::base_type(banner)
    {
        // GNU gdb 6.3.50-20050815 (Apple version gdb-1705) (Fri Jul  1 10:50:06 UTC 2011)\nCopyright 2004 Free Software Foundation, Inc.\n
        // GNU gdb (Ubuntu/Linaro 7.2-1ubuntu11) 7.2
        version_number = +(qi::alnum | qi::char_('.') | qi::char_('-') | qi::char_('/'));
        paren_expr = qi::char_('(') > (version_number % qi::char_(' ')) > qi::char_(')');
        version_or_expr = paren_expr | version_number;
        banner_line = +(qi::char_ - '\n');
        banner_message = banner_line > *(qi::char_('\n') >> banner_line);
        banner = qi::lit("GNU gdb ") >> version_or_expr > banner_message > qi::lit("\n");
    }

    qi::rule<Iterator, std::string()> paren_expr;
    qi::rule<Iterator, std::string()> version_number;
    qi::rule<Iterator, std::string()> version_or_expr;
    qi::rule<Iterator, std::string()> banner_line;
    qi::rule<Iterator, std::string()> banner_message;
    qi::rule<Iterator, GdbResponses::Banner()> banner;
};

boost::spirit::qi::grammar<std::string::const_iterator, GdbResponses::Banner()>* gdb_banner_parse_grammar()
{
    return new GdbBannerGrammar();
}

    }
}


