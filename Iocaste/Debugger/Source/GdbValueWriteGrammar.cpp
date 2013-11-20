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
using namespace IoDbg::GdbResponses;

namespace IoDbg {

namespace karma = boost::spirit::karma;
typedef std::back_insert_iterator<std::string> OutputIterator;

struct GdbValueWriteGrammar
  : karma::grammar<OutputIterator, Rules::GdbValue()>
{
    GdbValueWriteGrammar()
      : GdbValueWriteGrammar::base_type(start), esc_grammar(string_escape_write_grammar())
    {
    }

    unique_ptr<
        karma::grammar<OutputIterator, std::string()>
    > esc_grammar;
    karma::rule<OutputIterator, Rules::GdbAddress()> address;
    karma::rule<OutputIterator, Rules::GdbStruct()> gdb_struct;
    karma::rule<OutputIterator, Rules::ValueAsFunctionPtr()> value_as_function_ptr;
    karma::rule<OutputIterator, Rules::ValueAsString()> value_as_string;
    karma::rule<OutputIterator, Rules::ValueElided()> value_elided;
    karma::rule<OutputIterator, string()> quoted_string;
    karma::rule<OutputIterator, Rules::GdbValue()> start;
};

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, Rules::GdbValue()>* gdb_value_write_grammar()
{
    return new GdbValueWriteGrammar();
}

}


