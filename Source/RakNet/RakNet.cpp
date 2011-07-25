// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/RakNet/Bindings.hpp"

#include "SocketLayer.h"
using namespace RakNet;

#include "LikeMagic/Utility/UserMacros.hpp"
#include "LikeMagic/MarkableObjGraph.hpp"

using namespace LikeMagic;

#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/IoBlock.hpp"
using LikeMagic::Backends::Io::IoBlock;


#include "StringTable.h"
#include "RakPeerInterface.h"

#include <stdio.h>
#include <string.h>
#include "BitStream.h"
#include "MessageIdentifiers.h"
#include "ReplicaManager3.h"
#include "NetworkIDManager.h"
#include "RakSleep.h"
#include "FormatString.h"
#include "RakString.h"
#include "GetTime.h"
#include "SocketLayer.h"
#include "Getche.h"
#include "Rand.h"
#include "Gets.h"

#pragma GCC diagnostic ignored "-Wsign-compare"
#include "VariableDeltaSerializer.h"

#include <pthread.h>


namespace Bindings { namespace RakNet {

DefaultMessageIDTypes GetPacketMessageId(Packet* p)
{
    if (!p)
        throw std::logic_error("Packet is null!");

    return static_cast<DefaultMessageIDTypes>(p->data[0]);
}

void add_bindings_raknet(RuntimeTypeSystem& type_sys)
{
    LM_STATIC_FUNC_NAME(type_sys, , "RakNet_GetTime", RakNet::GetTime)

    LM_CLASS(type_sys, SocketDescriptor)
    LM_CONSTR(SocketDescriptor,,)
    LM_FIELD(SocketDescriptor, (port))
    LM_ARRAY_FIELD(SocketDescriptor, (hostAddress))

    LM_CLASS(type_sys, RakPeerInterface)
    LM_STATIC_FUNC_NAME(type_sys, RakPeerInterface, "RakPeerInterface_GetInstance", GetInstance)
    LM_STATIC_FUNC_NAME(type_sys, RakPeerInterface, "RakPeerInterface_DestroyInstance", DestroyInstance)
    LM_FUNC(RakPeerInterface, (Startup)(Shutdown)(AttachPlugin)(Connect)(SetMaximumIncomingConnections)(Receive)(DeallocatePacket)
            (GetInternalID)(AdvertiseSystem)(IncrementNextSendReceipt))

    LM_CLASS(type_sys, SystemAddress)
    LM_CONSTR(SystemAddress,,)

    LM_CLASS(type_sys, RakNetGUID)
    LM_CONSTR(RakNetGUID,,)

    LM_CLASS(type_sys, Packet)
    LM_FIELD(Packet, (systemAddress)(guid)(length)(bitSize)(data))
    Packet_LM.bind_nonmember_op("GetMessageID", GetPacketMessageId);

    LM_ENUM(type_sys, DefaultMessageIDTypes)
    LM_ENUM(type_sys, StartupResult)

    LM_CLASS(type_sys, RakString)
    LM_CONSTR(RakString,,)
    LM_FUNC(RakString, (C_String))

    LM_CLASS(type_sys, PacketPriority)
    LM_CLASS(type_sys, PacketReliability)

    LM_CLASS(type_sys, PRO)
    LM_FIELD(PRO, (priority)(reliability)(orderingChannel)(sendReceipt))

    LM_CLASS(type_sys, Time)
}

}}
