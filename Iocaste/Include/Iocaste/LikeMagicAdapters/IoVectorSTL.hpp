// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "UArray.h"

#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"

#include <iterator>

namespace Iocaste { namespace LMAdapters {

template <typename T> struct UArrayElemConv;

template <typename T> struct UArrayElemConv<T*> { static T* do_conv(UArray* ua, size_t pos) { return reinterpret_cast<T*>(UArray_rawPointerAt_(ua, pos)); }};

template <> struct UArrayElemConv<double> { static double do_conv(UArray* ua, size_t pos) { return UArray_rawDoubleAt_(ua, pos); }};

template <> struct UArrayElemConv<long> { static long do_conv(UArray* ua, size_t pos) { return UArray_rawLongAt_(ua, pos); }};
template <> struct UArrayElemConv<short> { static short do_conv(UArray* ua, size_t pos) { return static_cast<short>(UArray_rawLongAt_(ua, pos)); }};

template <> struct UArrayElemConv<unsigned long> { static unsigned long do_conv(UArray* ua, size_t pos) { return static_cast<unsigned long>(UArray_rawLongAt_(ua, pos)); }};
template <> struct UArrayElemConv<unsigned short> { static unsigned short do_conv(UArray* ua, size_t pos) { return static_cast<unsigned short>(UArray_rawLongAt_(ua, pos)); }};


// Wraps an Io Vector as an STL-compliant C++ container
template <typename T>
class IoVectorSTL
{
private:
    UArray* uarray;

public:
    class const_iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    private:
        UArray* uarray;
        size_t pos;

    public:
        const_iterator(UArray* uarray_, size_t pos_=0)
            : uarray(uarray_), pos(pos_) {}

        T operator*() const
        {
            return UArrayElemConv<T>::do_conv(uarray, pos);
        }

        size_t operator -(const_iterator other) const { return this->pos - other.pos; }
        size_t operator --() { return --pos; }

        size_t operator +(const_iterator other) const { return this->pos + other.pos; }
        size_t operator ++() { return ++pos; }

    };

    IoVectorSTL(IoObject* self) : uarray(IoSeq_rawUArray(self)) { }

    const_iterator begin() const
    {
        return const_iterator(uarray);
    }

    const_iterator end() const
    {
        return const_iterator(uarray, size());
    }

    size_t size() const
    {
        return UArray_size(uarray);
    }

};

}}
