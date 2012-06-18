#pragma once

#include "pthread.h"
#include <iostream>

#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"

namespace Iocaste {
    namespace Debugger {

class Worker
{
private:
	pthread_t thread;
	AbstractInput<std::string>& input;
	AbstractOutput<std::string>& output;
	bool line_mode;
    std::string debug_name;
    std::ostream& debug_log;

	static void* callback(void* obj);
	volatile bool stop;
	volatile bool is_running;

	void run_loop();

public:
	Worker(AbstractInput<std::string>& input_, AbstractOutput<std::string>& output_, std::string debug_name_, std::ostream& debug_log_);
	virtual ~Worker();
	void stop_thread();
	bool is_stopped() const;
};

    }
}
