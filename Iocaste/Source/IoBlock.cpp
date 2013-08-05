// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

namespace Iocaste { namespace LikeMagicAdapters {

IoBlock::IoBlock()
    : iovm(0), io_block(0), io_target(0)
{
}

IoBlock::IoBlock(IoVM* iovm_, IoObject* io_block_, IoObject* io_target_)
    : iovm(iovm_), io_block(io_block_), io_target(io_target_)
{
    if (io_target && !io_target_->object)
        throw std::logic_error("Target has no object!");
}

IoBlock::IoBlock(IoBlock const& other)
    : iovm(other.iovm), io_block(other.io_block), io_target(other.io_target)
{
}

IoBlock& IoBlock::operator =(IoBlock const& other)
{
    //cout << "IoBlock " << this << " copy assigned from " << &other << ", iovm was " << iovm << " block is " << this->io_block <<" target is " << this->io_target << endl;
    iovm = other.iovm;
    io_block = other.io_block;
    io_target = other.io_target;
    //cout << "Now iovm is " << iovm << " block is " << this->io_block <<" target is " << this->io_target << endl;
    return *this;
}

IoBlock::~IoBlock()
{
    //cout << "IoBlock " << this << " destructed, target was " << this->io_target << endl;
    this->io_target = (IoObject*)0xA5A5A5A5;
}

#define DATA(self) ((IoBlockData *)IoObject_dataPointer(self))

void IoBlock::add_arg(IoMessage* m, ExprPtr expr) const
{
    if (!m->object)
        throw std::logic_error("Invalid message target; message object is null");

    IoMessage_addCachedArg_(m, iovm->to_script(io_block, io_block, m, expr));
}

IoObject* IoBlock::activate(IoMessage* m) const
{
    if (!io_block)
        throw std::logic_error("io_block is null!");

    if (!io_target)
        throw std::logic_error("io_target is null!");

    if (!m)
        throw std::logic_error("message is null!");

	IoBlockData* blockData = (IoBlockData *)IoObject_dataPointer(io_block);
	if (!blockData)
        throw std::logic_error("block data is null!");

    // Apparently Io doesn't export IoBlock_activate, but hopefully IoObject_activate works just as well.
    //IoObject* result = IoObject_activate(io_block, io_target, io_target, m, io_target);
    // Unfortunately IoObject_activate is NOT the same; need IoBlock_activate to be exported.
    IoObject* result = IoBlock_activate(io_block, io_target, io_target, m, io_target);

    {

        if (iovm->last_exception)
        {
            iovm->last_exception = 0;
            throw std::logic_error("LikeMagic IoBlock activate: Caught Io exception while running an Io block.");
        }
    }

    if (!result)
        throw std::logic_error("Error in IoBlock: activating the block returned null (may be caused by an error in script).");

    return result;
}

void IoBlock::mark() const
{
    IoObject_shouldMarkIfNonNull(io_block);
    IoObject_shouldMarkIfNonNull(io_target);
}

bool IoBlock::empty() const
{
    return !io_block;
}

}}
