
#include <boost/spirit/include/karma.hpp>

namespace Iocaste { namespace Debugger {

namespace karma = boost::spirit::karma;

template <typename OutputIterator>
struct StringEscapeWriter
  : karma::grammar<OutputIterator, std::string()>
{
    StringEscapeWriter()
      : StringEscapeWriter::base_type(start)
    {
        esc_char.add('\a', "\\a")('\b', "\\b")('\f', "\\f")('\n', "\\n")
                    ('\r', "\\r")('\t', "\\t")('\v', "\\v")('\\', "\\\\")
                    ('\'', "\\\'")('\"', "\\\"")('\0', "\\0")(26, "\\z")
            ;

        esc_str = *(esc_char | karma::print | karma::lit("\\x") << karma::hex << ';' );
        start %= esc_str;
    }

    karma::rule<OutputIterator, std::string()> start;
    karma::rule<OutputIterator, std::string()> esc_str;
    karma::symbols<char, char const*> esc_char;
};

}}
