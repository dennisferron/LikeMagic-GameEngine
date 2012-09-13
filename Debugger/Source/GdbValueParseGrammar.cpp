#include <boost/spirit/include/qi.hpp>
#include "SharedTypesFusion.hpp"
#include "ParseGrammars.hpp"

using namespace std;

namespace Iocaste {
    namespace Debugger {

namespace qi = boost::spirit::qi;

struct GdbValueParseGrammar : qi::grammar<std::string::const_iterator, SharedTypes::GdbValue()>
{
    typedef std::string::const_iterator Iterator;

    GdbValueParseGrammar() : GdbValueParseGrammar::base_type(start), unesc_grammar(string_unescape_parse_grammar())
    {
        start = (address | qi::int_ | quoted_string | gdb_struct | value_elided) >> -value_as_string >> -value_as_function_ptr;
        address = qi::lit("0x") > +qi::alnum;
        quoted_string = qi::lit('"') >> *unesc_grammar >> qi::lit('"');
        elipses = qi::string("...");
        value_elided = elipses;
        value_as_string = qi::lit(" ") >> quoted_string;
        value_as_function_ptr = qi::lit(" <") > +(qi::char_-'>') > ">";
    }

    unique_ptr<qi::grammar<std::string::const_iterator, std::string()>> unesc_grammar;
    qi::rule<Iterator, SharedTypes::GdbValue()> start;
    qi::rule<Iterator, SharedTypes::GdbAddress()> address;
    qi::rule<Iterator, std::string()> quoted_string;
    qi::rule<Iterator, SharedTypes::ValueElided()> value_elided;
    qi::rule<Iterator, std::string()> elipses;
    qi::rule<Iterator, SharedTypes::GdbStruct()> gdb_struct;
    qi::rule<Iterator, SharedTypes::ValueAsString()> value_as_string;
    qi::rule<Iterator, SharedTypes::ValueAsFunctionPtr()> value_as_function_ptr;
};

boost::spirit::qi::grammar<std::string::const_iterator, SharedTypes::GdbValue()>* gdb_value_parse_grammar()
{
    return new GdbValueParseGrammar();
}

    }
}
