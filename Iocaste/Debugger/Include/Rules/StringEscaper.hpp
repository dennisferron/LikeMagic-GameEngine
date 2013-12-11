#include "SpiritMacros.hpp"

SPIRIT_RULE((IoDbg)(Rules), std::string,
    esc_str,
        *(esc_char | (qi::print - qi::char_("\\\""))
            | (qi::lit("\\x")
                > qi::hex
                > qi::lit(";"))),
        *(esc_char | karma::print | karma::lit("\\x") << karma::hex << ';')
)

SPIRIT_SYMBOLS((IoDbg)(Rules),
    esc_char,
        esc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                      ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
                      ("\\\'", '\'')("\\\"", '\"')("\\0", '\0')("\\z", 26),
        esc_char.add('\a', "\\a")('\b', "\\b")('\f', "\\f")('\n', "\\n")
            ('\r', "\\r")('\t', "\\t")('\v', "\\v")('\\', "\\\\")
            ('\'', "\\\'")('\"', "\\\"")('\0', "\\0")(26, "\\z")
)
