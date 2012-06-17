#pragma once

#include "ProducerConsumerQueue.hpp"
#include "AbstractOutput.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T>
class QueueOutput :
    public AbstractOutput<T>
{
private:
    ProducerConsumerQueue<T>& queue;

public:
    QueueOutput(ProducerConsumerQueue<T>& queue_) :
        queue(queue_)
    {
    }

    virtual void WriteData(T const& data)
    {
        queue.push(data);
    }
};

    }
}
