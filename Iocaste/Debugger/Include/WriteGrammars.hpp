#include "GdbResponse.hpp"

#include <boost/spirit/include/karma.hpp>
#include <vector>

namespace IoDbg {

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, Rules::GdbValue()>* gdb_value_write_grammar();
boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, std::string()>* string_escape_write_grammar();
boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, std::vector<Rules::GdbResponseType>()>* response_write_grammar();

}

