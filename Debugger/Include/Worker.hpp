#pragma once

#include "pthread.h"

class Worker
{
private:
	pthread_t thread;
	istream& input;
	ostream& output;

	static void* callback(void* obj);
	volatile bool stop;
	void run_loop();

public:
	Worker(istream& input, ostream& output);
	~Worker();
	void stop_thread();
	void is_stopped();
};
