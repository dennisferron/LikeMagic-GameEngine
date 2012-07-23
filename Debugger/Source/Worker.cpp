#include "Worker.hpp"

using namespace std;
using namespace Iocaste::Debugger;

Worker::Worker(AbstractInput<string>& input_, AbstractOutput<string>& output_, string debug_name_, AbstractOutput<boost::exception_ptr>& errors_)
    :
        input(input_), output(output_),
        debug_name(debug_name_), errors(errors_),
        stop(false), is_running(false)
{
	is_running = true;
	thread = boost::thread(&Worker::run_loop, this);
}

Worker::~Worker()
{
	if (is_running)
		stop_thread();
}

void Worker::stop_thread()
{
	stop = true;
    thread.join();
}


void Worker::run_loop()
{
    try
    {
        std::string line;

        while (!stop)
        {
            if (input.HasData())
            {
                string s = input.ReadData();
                output.WriteData(s);
            }
            else
            {
                boost::this_thread::sleep(boost::posix_time::milliseconds(5));
            }
        }
    }
    catch (...)
    {
        errors.WriteData(boost::current_exception());
    }

    is_running = false;
}

bool Worker::is_stopped() const
{
    return !is_running;
}
