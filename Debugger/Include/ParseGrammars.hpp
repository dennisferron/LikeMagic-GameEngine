#include "GdbResponse.hpp"

#include <boost/spirit/include/qi.hpp>

namespace Iocaste { namespace Debugger {

boost::spirit::qi::grammar<std::string::const_iterator, GdbResponseType()>* response_parse_grammar(bool use_alt_parser);
boost::spirit::qi::grammar<std::string::const_iterator, SharedTypes::GdbValue()>* gdb_value_parse_grammar();
boost::spirit::qi::grammar<std::string::const_iterator, std::string()>* string_unescape_parse_grammar();
boost::spirit::qi::grammar<std::string::const_iterator, GdbResponses::Banner()>* gdb_banner_parse_grammar();

}}
