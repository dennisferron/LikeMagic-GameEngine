#include "GdbResponse.hpp"
using namespace IoDbg;
using namespace IoDbg::Rules;

#include "WriteGrammars.hpp"

#include "Exception.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace karma = boost::spirit::karma;
namespace ascii = boost::spirit::ascii;

#include <string>
#include <vector>
using namespace std;

#define KARMA_DECL
#include "Rules/SharedTypes.hpp"
#undef KARMA_DECL

#define KARMA_EXTERN
#include "Rules/GdbBanner.hpp"
#include "Rules/GdbValue.hpp"
#undef KARMA_EXTERN

#define KARMA_DECL
#include "Rules/Unactionable.hpp"
#include "Rules/Actionable.hpp"
#undef KARMA_DECL

using namespace IoDbg::Rules;
using namespace IoDbg::Rules::karma_rules;

namespace IoDbg {

extern boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, std::string()>* esc_grammar;
extern boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, Rules::GdbValue()>* gdb_value_grammar;

typedef std::back_insert_iterator<std::string> OutputIterator;

struct GdbResponseWriteGrammar
  : karma::grammar<OutputIterator, vector<GdbResponseType>()>
{
    GdbResponseWriteGrammar()
      : GdbResponseWriteGrammar::base_type(start)
    {
        start = *response_item;
    }

    karma::rule<OutputIterator, vector<GdbResponseType>()> start;
};

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, vector<GdbResponseType>()>* response_write_grammar()
{
    #define KARMA_DEFN
    #include "Rules/SharedTypes.hpp"
    #include "Rules/Unactionable.hpp"
    #include "Rules/Actionable.hpp"
    return new GdbResponseWriteGrammar();
}

}

