#pragma once

#include "Thread.hpp"
#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"

#include <queue>


namespace Iocaste
{
	namespace Debugger
	{

//! This queue is designed to be thread safe for one producer thread and one consumer thread.
template <typename T>
class Queue : public AbstractInput<T>, public AbstractOutput<T>
{
private:

    mutable pthread_mutex_t record_mutex;
    std::queue<T> entries;

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

public:

    Queue()
    {
        pthread_mutex_init(&record_mutex, NULL);
    }

    virtual bool HasData() const
    {
        return size() > 0;
    }

    virtual T ReadData()
    {
        while (!HasData())
            Thread::nice(1);

        return pop();
    }

    virtual void WriteData(T const& data)
    {
        push(data);
    }
};

}}
