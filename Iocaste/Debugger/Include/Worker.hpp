#pragma once

#include "boost/thread.hpp"
#include <iostream>

#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"
#include "Exception.hpp"

namespace Iocaste {
    namespace Debugger {

class Worker
{
private:
	boost::thread thread;
	AbstractInput<std::string>& input;
	AbstractOutput<std::string>& output;
    std::string debug_name;
	AbstractOutput<boost::exception_ptr>& errors;

	volatile bool stop;
	volatile bool is_running;

	void run_loop();

public:
	Worker(AbstractInput<std::string>& input_, AbstractOutput<std::string>& output_, std::string debug_name_, AbstractOutput<boost::exception_ptr>& errors_);
	virtual ~Worker();
	void stop_thread_now();
	void stop_thread_soon();
	bool is_stopped() const;
};

    }
}
