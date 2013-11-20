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
#include "Rules/GdbBanner.hpp"
using namespace IoDbg::Rules::qi_rules;
#undef QI_DECL

namespace IoDbg {

struct GdbBannerGrammar : qi::grammar<std::string::const_iterator, Rules::Banner()>
{
    typedef std::string::const_iterator Iterator;

    GdbBannerGrammar() : GdbBannerGrammar::base_type(banner)
    {
    }
};

boost::spirit::qi::grammar<std::string::const_iterator, Rules::Banner()>* gdb_banner_parse_grammar()
{
    #define QI_DEFN
    #include "Rules/GdbBanner.hpp"
    return new GdbBannerGrammar();
}

}


