#include "LookForPrompt.hpp"
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace Iocaste::Debugger;

LookForPrompt::LookForPrompt(
     AbstractOutput<std::string>& output_,
     AbstractInput<std::string>& end_marker_queue_)
        : buffer(), end_marker_str("(gdb) "), output(output_), end_marker_queue(end_marker_queue_)
{
}

void LookForPrompt::WriteData(string const& data)
{
    buffer.append(data);

    if (end_marker_queue.HasData())
        end_marker_str = end_marker_queue.ReadData();

    bool read_finished =
        boost::algorithm::ends_with(
            buffer,
            end_marker_str);

    if (read_finished && buffer.size() > 0)
    {
        output.WriteData(buffer);
        buffer.clear();
    }
}

