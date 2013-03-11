#include "WriteGrammars.hpp"

#include "Exception.hpp"


#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
using namespace Iocaste::Debugger;

#include <string>
using namespace std;


#include "SharedTypesFusion.hpp"
using namespace Iocaste::Debugger::GdbResponses;

namespace Iocaste { namespace Debugger {

namespace karma = boost::spirit::karma;
typedef std::back_insert_iterator<std::string> OutputIterator;

struct GdbValueWriteGrammar
  : karma::grammar<OutputIterator, SharedTypes::GdbValue()>
{
    GdbValueWriteGrammar()
      : GdbValueWriteGrammar::base_type(start), esc_grammar(string_escape_write_grammar())
    {
        start = (address | karma::int_ | quoted_string | gdb_struct | value_elided)
            << -value_as_string << -value_as_function_ptr;
        address = karma::lit("0x") << karma::string;
        quoted_string = karma::lit("\"") << *esc_grammar << "\"";
        gdb_struct = karma::lit("{") << karma::string << "}";
        value_elided = karma::string;
        value_as_string = karma::lit(" ") << quoted_string;
        value_as_function_ptr = karma::lit(" <") << karma::string << ">";
    }

    unique_ptr<
        karma::grammar<OutputIterator, std::string()>
    > esc_grammar;
    karma::rule<OutputIterator, SharedTypes::GdbAddress()> address;
    karma::rule<OutputIterator, SharedTypes::GdbStruct()> gdb_struct;
    karma::rule<OutputIterator, SharedTypes::ValueAsFunctionPtr()> value_as_function_ptr;
    karma::rule<OutputIterator, SharedTypes::ValueAsString()> value_as_string;
    karma::rule<OutputIterator, SharedTypes::ValueElided()> value_elided;
    karma::rule<OutputIterator, string()> quoted_string;
    karma::rule<OutputIterator, SharedTypes::GdbValue()> start;
};

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, SharedTypes::GdbValue()>* gdb_value_write_grammar()
{
    return new GdbValueWriteGrammar();
}

}}


