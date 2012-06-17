#pragma once

#include "ProducerConsumerQueue.hpp"
#include "AbstractInput.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T>
class QueueInput :
    public AbstractInput<T>
{
private:
    ProducerConsumerQueue<T>& queue;

public:

    QueueInput(ProducerConsumerQueue<T>& queue_) :
        queue(queue_)
    {
    }

    virtual bool HasData() const
    {
        return queue.size() > 0;
    }

    virtual T ReadData()
    {
        return queue.pop();
    }
};

    }
}
