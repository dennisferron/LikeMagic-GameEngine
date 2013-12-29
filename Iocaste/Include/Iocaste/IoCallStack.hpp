
#pragma once

struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;
typedef IoObject IoError;
typedef IoObject IoCall;

#include <vector>

#include "Iocaste/IoCallData.hpp"

namespace Iocaste
{
    enum class MarkReason
    {
        TryBlock,
        MessageFrame,
        Unspecified
    };

    class IoCallStack
    {
    public:
        typedef std::size_t mark_type;
        typedef typename std::vector<IoObject*>::const_reverse_iterator const_reverse_iterator;
        typedef typename std::vector<IoObject*>::const_iterator const_iterator;

    private:

        struct Mark
        {
            std::size_t index;
            MarkReason reason;
        };

        std::vector<IoObject*> items;
        std::vector<Mark> marks;

    public:

        IoObject* top() const;

        std::size_t size();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        const_iterator begin() const;
        const_iterator end() const;

        // Replaces IoState_clearRetainStack
        void clear();

        // Replaces IoState_clearTopPool
        void clear_to_last_mark();

        // Replaces IoState_popRetainPool_( , uintptr_t mark)
        void pop_to_mark_point(mark_type mark);

        // Replaces IoState_popRetainPool
        void pop_mark();

        void do_(StackDoCallback *callback) const;

        // Replaces IoState_pushRetainPool
        mark_type push_mark(MarkReason reason);

        // Used in IoState_unreferencedStackRetain_
        void retain_data(IoObject* io_obj);

        // Used in IoState_retainCall_ to replace IoState_addValueIfNecessary_ for IoCall_new
        void retain_call(IoCall* io_call);

        void mark() const;
    };
}
