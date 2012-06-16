#pragma once

#include "ProducerConsumerQueue.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T>
class QueueOutput :
    public AbstractOutput
{
private:
    ProducerConsumerQueue<T>& queue;

public:
    virtual void WriteData(T const& data)
    {
        queue.push(data);
    }
};

    }
}
