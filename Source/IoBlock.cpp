// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Backends/Io/IoBlock.hpp"
#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"

#ifdef USE_DMALLOC
#include "dmalloc.h"
#endif

extern "C" {
    extern clock_t collection_began;
    extern clock_t collection_ended;
    extern int collection_cycle;
}

namespace LikeMagic { namespace Backends { namespace Io {

IoBlock::IoBlock()
    : type_sys(0), iovm(0), io_block(0), io_target(0), mark_count(0) {}

IoBlock::IoBlock(AbstractTypeSystem const* type_sys_, IoVM* iovm_, IoObject* io_block_, IoObject* io_target_)
    : type_sys(type_sys_), iovm(iovm_), io_block(io_block_), io_target(io_target_), mark_count(0)
{
    //check();

    if (io_target && !io_target_->object)
        throw std::logic_error("Target has no object!");

    if (iovm)
        iovm->check_blocks.insert(this);

    if (iovm && io_block_)
    {
        //Collector_retain_(iovm->state->collector, io_block_);
    }
}

IoBlock::IoBlock(IoBlock const& other)
    : type_sys(other.type_sys), iovm(other.iovm), io_block(other.io_block), io_target(other.io_target), mark_count(other.mark_count)
{
    //check();

    //if (iovm)
    //    iovm->check_blocks.insert(this);
}

IoBlock::~IoBlock()
{
    //if (iovm)
    //    iovm->check_blocks.erase(this);
}

#define DATA(self) ((IoBlockData *)IoObject_dataPointer(self))

void IoBlock::check() const
{
    return;

    try
    {
        if (!this)
            throw std::logic_error("IoBlock object 'this' is NULL!");

#ifdef USE_DMALLOC

        //if (iovm && io_block)
        //    iovm->check_gc("block", io_block);

        if (io_block)
        {
            if (io_block->next == (void*)0xdfdfdfdfdfdfdfdf)
                throw std::logic_error("io_block is in freed memory!");

            if (io_block->next == (void*)0xdadadadadadadada)
                throw std::logic_error("io_block is in uninitialized memory!");

            if (io_block->object == (void*)0xdfdfdfdfdfdfdfdf)
                throw std::logic_error("io_block is in freed memory!");

            if (io_block->object == (void*)0xdadadadadadadada)
                throw std::logic_error("io_block is in uninitialized memory!");
        }


        if (io_block && dmalloc_verify(io_block) == DMALLOC_VERIFY_ERROR)
        {
            if (!iovm)
                cout << "no io vm" << endl;
            else
            {
                iovm->check_gc("deallocated block", io_block);
                iovm->check_gc("deallocated block", io_block, "black", (iovm->state->collector->blacks));
            }
            throw std::logic_error("IoBlock block object at " + boost::lexical_cast<string>(io_block) + " points to invalid memory.");
        }

        if (io_target && dmalloc_verify(io_target) == DMALLOC_VERIFY_ERROR)
            throw std::logic_error("IoBlock target points to invalid memory.");

        if (io_target && dmalloc_verify(DATA(io_target)) == DMALLOC_VERIFY_ERROR)
            throw std::logic_error("IoBlock target data points to invalid memory.");
#endif

    }
    catch(...)
    {
        if (!iovm)
            cout << "Block has no iovm!" << endl;
        else
        {
            cout << "Checking color: " << endl;
            iovm->check_gc("deallocated block", io_block);
            iovm->check_gc("deallocated block", io_block, "black", (iovm->state->collector->blacks));
            cout << "Done checking color." << endl;
        }

        cout << "Block was marked this many times: " << mark_count << endl;
        cout << "Most recent collection cycle: " << collection_cycle << " Began: " << collection_began << "  Ended: " << collection_ended << " Block last marked: " << last_mark_time << " in cycle: " << last_collection_cycle << endl;

        throw;
    }

}

void IoBlock::add_arg(IoMessage* m, AbstractCppObjProxy* proxy) const
{
    if (!m->object)
        throw std::logic_error("Invalid message target; message object is null");

    IoMessage_addCachedArg_(m, iovm->to_script(io_block, io_block, m, proxy));
}

IoObject* IoBlock::activate(IoMessage* m) const
{
    //check();

    //cout << "IoBlock::activate " << get_debug_name() << "   ";

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

        //IoCoroutine *self = iovm->state->currentCoroutine;

        /*   This isn't how to handle exceptions - Io would have already exited by now:
        if (!ISNIL(IoCoroutine_rawException(self)))
        {
            IoCoroutine_rawPrintBackTrace(self);
            throw std::logic_error("Io Exception; see back trace above.");
        }
        */
    }

    if (!result)
        throw std::logic_error("Error in IoBlock: activating the block returned null (may be caused by an error in script).");

    return result;
}

void IoBlock::mark() const
{
    if (io_block)
        ++mark_count;

    last_mark_time = clock();
    last_collection_cycle = collection_cycle;

    //check();
/*
    if (iovm && iovm->watch_freed_objects())
    {
        if(io_block && iovm->check_if_freed(io_block))
            throw std::logic_error("IoBlock object freed before it could be marked, IoBlock debug name = " + get_debug_name());

        if (io_target && iovm->check_if_freed(io_target))
            throw std::logic_error("IoBlock target freed before it could be marked, IoBlock debug name = " + get_debug_name());
    }
*/

    //std::cout << "Marking IoBlock, block = " << io_block << ", target = " << io_target << std::endl;
    IoObject_shouldMarkIfNonNull(io_block);

    //if (io_block && iovm && iovm->is_white(io_block))
    //    throw std::logic_error("Block is white after being marked!");

    IoObject_shouldMarkIfNonNull(io_target);
}

bool IoBlock::empty() const
{
    return !io_block;
}

}}}
