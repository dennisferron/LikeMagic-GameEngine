// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Backends/Io/IoBlock.hpp"
#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"

namespace LikeMagic { namespace Backends { namespace Io {

IoBlock::IoBlock()
    : type_sys(0), iovm(0), io_block(0), io_target(0) {}

IoBlock::IoBlock(AbstractTypeSystem const* type_sys_, IoVM* iovm_, IoObject* io_block_, IoObject* io_target_)
    : type_sys(type_sys_), iovm(iovm_), io_block(io_block_), io_target(io_target_)
    {
        if (!io_target_->object)
            throw std::logic_error("Target has no object!");
    }

void IoBlock::add_arg(IoMessage* m, AbstractCppObjProxy* proxy) const
{
    if (!m->object)
        throw std::logic_error("Invalid message target; message object is null");

    IoMessage_addCachedArg_(m, iovm->to_script(io_block, io_block, m, proxy));
}

IoObject* IoBlock::activate(IoMessage* m) const
{
    // Apparently Io doesn't export IoBlock_activate, but hopefully IoObject_activate works just as well.
    IoObject* result = IoObject_activate(io_block, io_target, io_target, m, io_target);

    {
        IoCoroutine *self = iovm->self->currentCoroutine;

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
    //std::cout << "Marking IoBlock, block = " << io_block << ", target = " << io_target << std::endl;
    IoObject_shouldMarkIfNonNull(io_block);
    IoObject_shouldMarkIfNonNull(io_target);
}

bool IoBlock::empty() const
{
    return !io_block;
}

}}}
