#include "LookForPrompt.hpp"
#include "boost/algorithm/string/predicate.hpp"

using namespace std;
using namespace Iocaste::Debugger;

LookForPrompt::LookForPrompt(
     AbstractOutput<StringWithPrompt>& output_,
     AbstractInput<std::string>& end_marker_queue_)
        : buffer(), end_marker_str("(gdb) "), output(output_), end_marker_queue(end_marker_queue_)
{
}

void LookForPrompt::WriteData(string const& data)
{
    buffer.append(data);

    if (end_marker_queue.HasData())
    {
        // Save the old end marker and continue to look for it
        // until we see the first string with the new end marker.
        old_end_marker = end_marker_str;
        end_marker_str = end_marker_queue.ReadData();
    }

    bool read_finished = false;

    // Look for the new marker first
    if (boost::algorithm::ends_with(
            buffer, end_marker_str))
    {
        read_finished = true;
        // OK we saw the new prompt,
        // so we can stop looking for the old one.
        old_end_marker.reset();
    }
    else if(old_end_marker.is_initialized()
        && boost::algorithm::ends_with(
            buffer, *old_end_marker))
    {
        // Got a message still using the old prompt.
        // We can keep doing this until the old prompt is reset.
        read_finished = true;
    }

    if (read_finished)
    {
        buffer.erase(buffer.end() - end_marker_str.size(), buffer.end());
        output.WriteData( { buffer, end_marker_str } );
        buffer.clear();
    }
}

