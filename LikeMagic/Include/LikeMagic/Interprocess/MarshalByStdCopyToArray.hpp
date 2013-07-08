#pragma once

#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/Interprocess/AbstractSharedArgMarshaller.hpp"

namespace LikeMagic { namespace Interprocess {

template <typename T>
struct ReferenceToSharedArray
{
    ReferenceToSharedArray(boost::offset_ptr<T> data_, size_t size_)
        : data(data_), size(size_) {}

    boost::offset_ptr<T> data;
    size_t size;
};

class SharedMemoryAllocator
{
public:
    template <typename T> ReferenceToSharedArray<T> allocate(size_t count);
    template <typename T> void release(ReferenceToSharedArray<T> reference);
};

template <typename ContainerType, typename ElementType>
struct MarshalByStdCopyToArray : public AbstractSharedArgMarshaller
{
    LikeMagic::AbstractTypeSystem const& type_system;
    LikeMagic::Interprocess::SharedMemoryAllocator& allocator;

    MarshalByCopy(LikeMagic::AbstractTypeSystem const& type_system_, SharedMemoryAllocator allocator)
        : type_system(type_system_) {}

    virtual void write(void* location, ExprPtr arg)
    {
        Container container = type_system.try_conv<T>(arg);
        size_t size = container.size();
        offset_ptr<T> buffer = allocator.allocate_buffer<ElementType>(size);
        std::copy(container.begin(), container.end(), buffer.data);
        *reinterpret_cast<ReferenceToSharedArray<ElementType>*>(location) =
            ReferenceToSharedArray<ElementType>(data, size);
    }

    virtual ExprPtr read(void* location)
    {
        ReferenceToSharedArray<ElementType> buffer =
            *reinterpret_cast<ReferenceToSharedArray<ElementType>*>(location);
        return Term<T, true>::create(Container(buffer.data, buffer.data + size));
    }

    virtual size_t size() const
    {
        return sizeof(ReferenceToSharedArray<ElementType>);
    }

    virtual void release(ExprPtr expr)
    {
        ReferenceToSharedArray<ElementType> buffer = type_system.try_conv<T>(arg);
        allocator.release(buffer);
    }
};

}}
