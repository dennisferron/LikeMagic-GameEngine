
#include "Iocaste/Stack.hpp"
#include "Iocaste/CShims/Stack.h"
#include "Iocaste/IoCallStack.hpp"

#include "List.h"

#include <vector>
using namespace std;

void IoCallStack::push(IoCallData const& item)
{
    items.push_back(item);
}

mark_type IoCallStack::push_mark_point()
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

std::size_t IoCallStack::size()
{
    return items.size();
}

const_reverse_iterator IoCallStack::rbegin() const
{
    return items.rbegin();
}

const_reverse_iterator IoCallStack::rend() const
{
    return items.rend();
}

reverse_iterator IoCallStack::begin() const
{
    return items.begin();
}

reverse_iterator IoCallStack::end() const
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

typedef Iocaste::IoCallStack::mark_type mark_type;
