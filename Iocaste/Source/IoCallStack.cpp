
#include "Iocaste/Stack.hpp"
#include "Iocaste/CShims/Stack.h"
#include "Iocaste/IoCallStack.hpp"

#include "IoObject_inline.h"

using namespace Iocaste;

#include "List.h"

#include <stdexcept>
#include <vector>
using namespace std;

void IoCallStack::stack_retain(IoObject* io_obj)
{
    if (items.size() == 0)
        this->stack_retained.push_back(io_obj);
    else
        top().stack_retained.push_back(io_obj);
}

void IoCallStack::mark() const
{
    for (auto& retained_objs : this->stack_retained)
        IoObject_shouldMark(retained_objs);

    for (auto& call_data : items)
    {
        IoObject_shouldMark(call_data.sender);
        IoObject_shouldMark(call_data.target);
        IoObject_shouldMark(call_data.message);
        IoObject_shouldMark(call_data.slotContext);
        IoObject_shouldMark(call_data.activated);
        IoObject_shouldMark(call_data.coroutine);

        for (auto& retained_objs : call_data.stack_retained)
            IoObject_shouldMark(retained_objs);
    }
}

void IoCallStack::push(IoCallData const& item)
{
    items.push_back(item);
}

IoCallStack::mark_type IoCallStack::push_mark_point()
{
    marks.push_back(items.size());
    return marks.size()-1;
}

IoCallData IoCallStack::pop()
{
    IoCallData result = items.back();
    items.pop_back();
    return result;
}

void IoCallStack::pop_to_mark_point(mark_type mark)
{
    items.erase(items.begin() + marks[mark], items.end());
    marks.erase(marks.begin() + mark, marks.end());
}

void IoCallStack::pop_mark()
{
    pop_to_mark_point(marks.size()-1);
}

IoCallData const& IoCallStack::top() const
{
    return items.back();
}

IoCallData& IoCallStack::top()
{
    if (items.size() == 0)
        throw std::logic_error("tried to get top of empty stack");

    return items.back();
}

std::size_t IoCallStack::size()
{
    return items.size();
}

IoCallStack::const_reverse_iterator IoCallStack::rbegin() const
{
    return items.rbegin();
}

IoCallStack::const_reverse_iterator IoCallStack::rend() const
{
    return items.rend();
}

IoCallStack::const_iterator IoCallStack::begin() const
{
    return items.begin();
}

IoCallStack::const_iterator IoCallStack::end() const
{
    return items.end();
}

void IoCallStack::clear()
{
    items.clear();
    marks.clear();
}

void IoCallStack::clear_to_last_mark()
{
    items.erase(items.begin() + marks.back(), items.end());
}
