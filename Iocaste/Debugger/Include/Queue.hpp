#pragma once

#include "boost/thread.hpp"
#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"

#include <queue>


namespace IoDbg {

template <typename T>
class Queue : public AbstractInput<T>, public AbstractOutput<T>
{
private:

    mutable boost::mutex record_mutex;
    std::queue<T> entries;

    size_t size() const
    {
        boost::mutex::scoped_lock lock(record_mutex);
        return entries.size();
    }

    T pop()
    {
        boost::mutex::scoped_lock lock(record_mutex);
        T record = entries.front();
        entries.pop();
        return record;
    }

    void push(T const& value)
    {
        boost::mutex::scoped_lock lock(record_mutex);
        entries.push(value);
    }

public:

    Queue()
    {
    }

    virtual bool HasData() const
    {
        return size() > 0;
    }

    virtual T ReadData()
    {
        while (!HasData())
            boost::this_thread::sleep(
                boost::posix_time::milliseconds(5)
              );

        return pop();
    }

    virtual void WriteData(T const& data)
    {
        push(data);
    }
};

}
