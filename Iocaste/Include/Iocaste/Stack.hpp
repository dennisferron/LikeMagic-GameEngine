
#pragma once

struct IoState;
struct CollectorMarker;
typedef CollectorMarker IoObject;
typedef IoObject IoMessage;
typedef IoObject IoError;

#include <vector>

namespace Iocaste
{
    template <typename T>
    class Stack
    {
    public:
        typedef std::size_t mark_type;
        typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;

    private:
        std::vector<T> items;
        std::vector<std::size_t> marks;

    public:

        void push(T const& item)
        {
            items.push_back(item);
        }

        mark_type push_mark_point()
        {
            marks.push_back(items.size());
            return marks.size()-1;
        }

        T pop()
        {
            T result = items.back();
            items.pop_back();
            return result;
        }

        void pop_to_mark_point(mark_type mark)
        {
            items.erase(items.begin() + marks[mark], items.end());
            marks.erase(marks.begin() + mark, marks.end());
        }

        void pop_mark()
        {
            pop_to_mark_point(marks.size()-1);
        }

        T const& top() const
        {
            return items.back();
        }

        std::size_t size()
        {
            return items.size();
        }

        const_reverse_iterator rbegin() const
        {
            return items.rbegin();
        }

        const_reverse_iterator rend() const
        {
            return items.rend();
        }

        void clear()
        {
            items.clear();
            marks.clear();
        }

        void clear_to_last_mark()
        {
            items.erase(items.begin() + marks.back(), items.end());
        }
    };
}
