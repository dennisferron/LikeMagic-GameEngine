#include "GdbResponse.hpp"

#include <boost/spirit/include/qi.hpp>

namespace IoDbg {

boost::spirit::qi::grammar<std::string::const_iterator, Rules::GdbResponseType()>* response_parse_grammar(bool use_alt_parser);
boost::spirit::qi::grammar<std::string::const_iterator, Rules::GdbValue()>* gdb_value_parse_grammar();
boost::spirit::qi::grammar<std::string::const_iterator, std::string()>* string_unescape_parse_grammar();
boost::spirit::qi::grammar<std::string::const_iterator, Rules::Banner()>* gdb_banner_parse_grammar();

}
