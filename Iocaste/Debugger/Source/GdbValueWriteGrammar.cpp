#include "WriteGrammars.hpp"

#include "Exception.hpp"


#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
using namespace IoDbg;

#include <string>
using namespace std;


#include "SharedTypesFusion.hpp"
using namespace IoDbg::Rules;

namespace IoDbg {

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, Rules::GdbValue()>* gdb_value;
extern boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, std::string()>* esc_grammar;

namespace karma = boost::spirit::karma;
typedef std::back_insert_iterator<std::string> OutputIterator;

struct GdbValueWriteGrammar
  : karma::grammar<OutputIterator, Rules::GdbValue()>
{
    GdbValueWriteGrammar()
      : GdbValueWriteGrammar::base_type(start)
    {
        // TODO:  Set start rule
    }

    karma::rule<OutputIterator, Rules::GdbValue()> start;
};

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, Rules::GdbValue()>* gdb_value_write_grammar()
{
    // TODO: Define grammar
    return new GdbValueWriteGrammar();
}

}


