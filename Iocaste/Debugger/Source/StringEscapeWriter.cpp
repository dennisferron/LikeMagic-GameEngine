
#define DECL_STRUCTS
#define KARMA_DECL
#include "Rules/StringEscaper.hpp"
#undef KARMA_DECL
#undef DECL_STRUCTS

using namespace IoDbg;
using namespace IoDbg::Rules;
using namespace IoDbg::Rules::karma_rules;

namespace karma = boost::spirit::karma;

struct StringEscapeWriter : karma::grammar<OutputIterator, std::string()>
{
    StringEscapeWriter()
      : StringEscapeWriter::base_type(start)
    {
        start %= esc_str;
    }

    karma::rule<OutputIterator, std::string()> start;
    karma::rule<OutputIterator, std::string()> esc_str;
    karma::symbols<char, char const*> esc_char;
};

namespace IoDbg {

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, std::string()>* string_escape_write_grammar()
{
#define KARMA_DEFN
    #include "Rules/StringEscaper.hpp"
#undef KARMA_DEFN
    return new StringEscapeWriter();
}

}
