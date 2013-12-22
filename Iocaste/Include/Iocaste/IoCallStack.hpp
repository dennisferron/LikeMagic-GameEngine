
#pragma once

struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;
typedef IoObject IoError;

#include <vector>

#include "Iocaste/IoCallData.hpp"

namespace Iocaste
{
    class IoCallStack
    {
    public:
        typedef std::size_t mark_type;
        typedef typename std::vector<IoCallData>::const_reverse_iterator const_reverse_iterator;
        typedef typename std::vector<IoCallData>::const_iterator const_iterator;

    private:
        std::vector<IoCallData> items;
        std::vector<std::size_t> marks;
        std::vector<IoObject*> stack_retained;

    public:

        void push(IoCallData const& item);
        IoCallData pop();

        void pop_to_mark_point(mark_type mark);
        void pop_mark();

        IoCallData const& top() const;
        IoCallData& top();

        std::size_t size();

        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        const_iterator begin() const;
        const_iterator end() const;

        void clear();

        // Same as Stack_clearTop
        void clear_to_last_mark();

        void do_(StackDoCallback *callback) const;
        mark_type push_mark_point();

        void clearTop();

        void stack_retain(IoObject* io_obj);

        void mark() const;
    };
}
