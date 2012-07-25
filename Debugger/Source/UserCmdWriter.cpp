#include "UserCmdWriter.hpp"
#include "Exception.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/karma.hpp>
using namespace Iocaste::Debugger;

#include <string>
using namespace std;

BOOST_FUSION_ADAPT_STRUCT(
    UserSetOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd,
    (boost::optional<std::string>, raw_string)
    (boost::optional<UserSetOption>, set_option)
)

namespace karma = boost::spirit::karma;

template <typename OutputIterator>
struct UserCmdWriteGrammar
  : karma::grammar<OutputIterator, UserCmd()>
{
    UserCmdWriteGrammar()
      : UserCmdWriteGrammar::base_type(start)
    {
        raw_str = karma::string;
        set_option = karma::lit("set") << karma::string << -karma::string << karma::string;
        start = raw_str | set_option;
    }

    karma::rule<OutputIterator, std::string()> raw_str;
    karma::rule<OutputIterator, UserSetOption()> set_option;
    karma::rule<OutputIterator, UserCmd()> start;
};

void UserCmd::Write(std::string& generated) const
{
    namespace karma = boost::spirit::karma;

    typedef std::back_insert_iterator<std::string> sink_type;

    sink_type sink(generated);

    UserCmdWriteGrammar<sink_type> g;

    if(!karma::generate(sink, g, *this))
        throw boost::enable_current_exception(GeneratorException("Error writing activity log line."));
}


UserCmdWriter::UserCmdWriter(AbstractOutput<std::string>& sink_)
    : sink(sink_) {}

void UserCmdWriter::WriteData(UserCmd const& input)
{
    string result;
    input.Write(result);
    cerr << "Wrote: " << result << endl;
    sink.WriteData(result);

//    if (input.raw_string)
//        sink.WriteData(*input.raw_string);
//    else if (input.set_option)
//    {
//        std::cerr << "Got " << input.set_option->name << " " << (input.set_option->modifier? *(input.set_option->modifier) : "") << input.set_option->value << std::endl;
//    }
//    else
//        throw GeneratorException("No fields set on UserCmd");
}
