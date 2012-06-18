#include "LookForPrompt.hpp"
#include <boost/algorithm/string/predicate.hpp>


using namespace std;
using namespace Iocaste::Debugger;

LookForPrompt::LookForPrompt(ProducerConsumerQueue<std::string>& queue_, std::string end_marker_) :
    buffer(), queue(queue_), end_marker(end_marker_)
{
    pthread_mutex_init(&end_marker_mutex, NULL);
}

void LookForPrompt::WriteData(string const& data)
{
    buffer.append(data);

    string marker = get_end_marker();
    if (boost::algorithm::ends_with(buffer, marker))
    {
        queue.push(buffer);
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
