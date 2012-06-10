#include "Worker.hpp"

Worker::Worker()
{
	//pthread_mutex_init(&record_mutex, NULL);
	pthread_create(&thread, NULL, Worker::callback, this);
}

Worker::~Worker()
{
	if (!stop)
		stop_thread();
}

void Worker::stop_thread()
{
	stop = true;
	pthread_join(thread, NULL);
	//pthread_mutex_destroy(&record_mutex);
}

void* LogDaemon::callback(void* obj)
{
	static_cast<LogDaemon*>(obj)->run_loop();
	return NULL;
}
