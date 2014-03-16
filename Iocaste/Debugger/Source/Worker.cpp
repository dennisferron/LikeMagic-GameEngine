#include "Worker.hpp"

using namespace std;
using namespace IoDbg;

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
	// Unfortunately if we wait for join, threads that are
	// stuck on blocking input from istreams will never finish.
	//if (is_running)
	//	stop_thread_now();
}

void Worker::stop_thread_now()
{
	cerr << "Waiting on thread " << debug_name << endl;
	stop = true;
    thread.join();
}

void Worker::stop_thread_soon()
{
	stop = true;
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
                boost::this_thread::sleep(boost::posix_time::milliseconds(1));
            }

            if (stop)
            {
                cerr << "Thread " << debug_name << " received stop command." << endl;
            }
        }

        cerr << "Thread " << debug_name << " has finished." << endl;
    }
//    catch (boost::exception const& e)
//    {
//        //cerr << e.what() << endl;
//        errors.WriteData(boost::current_exception());
//    }
    catch (TestException const& e)
    {
        cerr << "Test failed " << e.what() << endl;
        errors.WriteData(boost::current_exception());
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
