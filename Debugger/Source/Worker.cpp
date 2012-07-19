#include "Worker.hpp"

using namespace std;
using namespace Iocaste::Debugger;

Worker::Worker(AbstractInput<string>& input_, AbstractOutput<string>& output_, string debug_name_)
    :
        input(input_), output(output_),
        debug_name(debug_name_),
        stop(false), is_running(false)
{
	is_running = true;
	pthread_create(&thread, NULL, Worker::callback, this);
}

Worker::~Worker()
{
	if (is_running)
		stop_thread();
}

void Worker::stop_thread()
{
	stop = true;
    pthread_join(thread, NULL);
}

void* Worker::callback(void* obj)
{
	static_cast<Worker*>(obj)->run_loop();
	return NULL;
}

void Worker::run_loop()
{
    std::string line;

    while (!stop)
    {
        if (input.HasData())
        {
            string s = input.ReadData();
            output.WriteData(s);
        }
    }

    is_running = false;
}

bool Worker::is_stopped() const
{
    return !is_running;
}
