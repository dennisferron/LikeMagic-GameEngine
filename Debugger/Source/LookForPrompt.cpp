#include "LookForPrompt.hpp"
#include <boost/algorithm/string/predicate.hpp>

char const eof_char = 0x1A;  // CTRL-Z on Mac OSX

using namespace std;
using namespace Iocaste::Debugger;

LookForPrompt::LookForPrompt(
     AbstractOutput<std::string>& output_,
     std::string end_marker_)
        : buffer(), output(output_), end_marker(end_marker_)
{
    pthread_mutex_init(&end_marker_mutex, NULL);
}

void LookForPrompt::WriteData(string const& data)
{
    bool read_finished = false;

    buffer.append(data);

    read_finished = read_finished ||
        boost::algorithm::ends_with(
            buffer,
            get_end_marker());

    if (read_finished && buffer.size() > 0)
    {
        output.WriteData(buffer);
        buffer.clear();
    }
}

string LookForPrompt::get_end_marker() const
{
    pthread_mutex_lock(&end_marker_mutex);
    string result = end_marker;
    pthread_mutex_unlock(&end_marker_mutex);
    return result;
}

void LookForPrompt::set_end_marker(string end_marker_)
{
    pthread_mutex_lock(&end_marker_mutex);
    end_marker = end_marker_;
    pthread_mutex_unlock(&end_marker_mutex);
}
