#include <boost/spirit/include/qi.hpp>
#include "SharedTypesFusion.hpp"
#include "ParseGrammars.hpp"

using namespace std;

namespace IoDbg {

namespace qi = boost::spirit::qi;

struct GdbValueParseGrammar : qi::grammar<std::string::const_iterator, Rules::GdbValue()>
{
    typedef std::string::const_iterator Iterator;

    GdbValueParseGrammar() : GdbValueParseGrammar::base_type(start), unesc_grammar(string_unescape_parse_grammar())
    {
    }

    unique_ptr<qi::grammar<std::string::const_iterator, std::string()>> unesc_grammar;
    qi::rule<Iterator, Rules::GdbValue()> start;
    qi::rule<Iterator, Rules::GdbAddress()> address;
    qi::rule<Iterator, std::string()> quoted_string;
    qi::rule<Iterator, Rules::ValueElided()> value_elided;
    qi::rule<Iterator, std::string()> elipses;
    qi::rule<Iterator, Rules::GdbStruct()> gdb_struct;
    qi::rule<Iterator, Rules::ValueAsString()> value_as_string;
    qi::rule<Iterator, Rules::ValueAsFunctionPtr()> value_as_function_ptr;
};

boost::spirit::qi::grammar<std::string::const_iterator, Rules::GdbValue()>* gdb_value_parse_grammar()
{
    return new GdbValueParseGrammar();
}

}
