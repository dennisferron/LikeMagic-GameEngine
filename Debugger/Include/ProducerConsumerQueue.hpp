#pragma once

#include "Thread.hpp"

#include <queue>


namespace Iocaste
{
	namespace Debugger
	{

//! This queue is designed to be thread safe for one producer thread and one consumer thread.
template <typename T>
class ProducerConsumerQueue
{
private:

    mutable pthread_mutex_t record_mutex;
    std::queue<T> entries;

public:

    ProducerConsumerQueue()
    {
        pthread_mutex_init(&record_mutex, NULL);
    }

    size_t size() const
    {
        pthread_mutex_lock(&record_mutex);
        size_t sz = entries.size();
        pthread_mutex_unlock(&record_mutex);
        return sz;
    }

    T pop()
    {
        T record;
        pthread_mutex_lock(&record_mutex);
        record = entries.front();
        entries.pop();
        pthread_mutex_unlock(&record_mutex);
        return record;
    }

    void push(T const& value)
    {
        pthread_mutex_lock(&record_mutex);
        entries.push(value);
        pthread_mutex_unlock(&record_mutex);
    }
};

}}
