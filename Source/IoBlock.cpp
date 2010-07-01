// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
// 
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Backends/Io/IoBlock.hpp"
#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"

namespace LikeMagic { namespace Backends { namespace Io {

IoBlock::IoBlock()
    : type_sys(0), io_block(0), io_target(0) {}

IoBlock::IoBlock(AbstractTypeSystem const* type_sys_, IoObject* io_block_, IoObject* io_target_)
    : type_sys(type_sys_), io_block(io_block_), io_target(io_target_) {}

void IoBlock::add_arg(IoMessage* m, AbstractCppObjProxy* proxy) const
{
    IoMessage_addCachedArg_(m, to_script(io_block, io_block, m, proxy));
}

IoObject* IoBlock::activate(IoMessage* m) const
{
    return IoBlock_activate(io_block, io_target, io_target, m, io_target);
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