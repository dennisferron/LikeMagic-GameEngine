#pragma once

#include "pthread.h"
#include <iostream>

#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"

namespace Iocaste {
    namespace Debugger {

struct WorkerComponentTag {};

class Worker : public WorkerComponentTag
{
private:
	pthread_t thread;
	AbstractInput<std::string>& input;
	AbstractOutput<std::string>& output;
	bool line_mode;
    std::string debug_name;

	static void* callback(void* obj);
	volatile bool stop;
	volatile bool is_running;

	void run_loop();

public:
	Worker(AbstractInput<std::string>& input_, AbstractOutput<std::string>& output_, std::string debug_name_);
	virtual ~Worker();
	void stop_thread();
	bool is_stopped() const;
	void RunAsync();
	void RunSync();
};

    }
}
