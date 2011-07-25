// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Bindings/RakNet/Protos.hpp"
#include "LikeMagic/Utility/UserMacros.hpp"

#include "MessageIdentifiers.h"
#include "RakNetTypes.h"
#include "ReplicaManager3.h"
#include "PacketPriority.h"



using namespace std;
using namespace LikeMagic::Backends::Io;
using namespace RakNet;

namespace Bindings { namespace RakNet {

DLL_PUBLIC void add_protos(IoVM& vm)
{
    LM_ENUM_PROTOS(vm,
        (ID_CONNECTION_ATTEMPT_FAILED)
        (ID_NO_FREE_INCOMING_CONNECTIONS)
        (ID_CONNECTION_REQUEST_ACCEPTED)
        (ID_NEW_INCOMING_CONNECTION)
        (ID_DISCONNECTION_NOTIFICATION)
        (ID_CONNECTION_LOST)
        (ID_ADVERTISE_SYSTEM)
        (ID_SND_RECEIPT_LOSS)
        (ID_SND_RECEIPT_ACKED)
    )

    LM_ENUM_PROTOS(vm,
        (UNASSIGNED_SYSTEM_ADDRESS)
    )

    LM_ENUM_PROTOS(vm,
        (RM3SR_DO_NOT_SERIALIZE)
        (RM3SR_SERIALIZED_ALWAYS)
        (RM3SR_SERIALIZED_ALWAYS_IDENTICALLY)
    )

    LM_ENUM_PROTOS(vm,
        (IMMEDIATE_PRIORITY)(HIGH_PRIORITY)(MEDIUM_PRIORITY)(LOW_PRIORITY)
    )

    LM_ENUM_PROTOS(vm,
        (UNRELIABLE)(UNRELIABLE_SEQUENCED)(RELIABLE)(RELIABLE_ORDERED)(RELIABLE_SEQUENCED)(UNRELIABLE_WITH_ACK_RECEIPT)(RELIABLE_WITH_ACK_RECEIPT)(RELIABLE_ORDERED_WITH_ACK_RECEIPT)
    )
}

}}

