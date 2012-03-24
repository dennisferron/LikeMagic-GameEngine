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
#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/IoBlock.hpp"
using Iocaste::LikeMagicAdapters::IoBlock;


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


// ReplicaManager3 is in the namespace RakNet
using namespace RakNet;


namespace Bindings { namespace RakNet {


template <typename T>
struct DeserializationResult
{
    bool success;
    T value;

    DeserializationResult() : success(false) {}
    DeserializationResult(bool success_, T value_) : success(success_), value(value_) {}
    bool get_success() const { return success; }
    T get_value() const { return value; }
};

// A helper function to make it more convenient to deserialize variables in script
template <typename T>
DeserializationResult<T> deserialize_helper(VariableDeltaSerializer& vds, VariableDeltaSerializer::DeserializationContext* context)
{
    T value;
    bool success = vds.DeserializeVariable(context, value);
    return DeserializationResult<T>(success, value);
}


void add_bindings_serializers(RuntimeTypeSystem& type_sys)
{
    LM_CLASS_NO_COPY(type_sys, BitStream)
    LM_FUNC_OVERLOAD(BitStream, "ReadRakString", Read, bool, RakString&)

    typedef VariableDeltaSerializer::SerializationContext SerializationContext;
    LM_CLASS(type_sys, SerializationContext)
    LM_CONSTR(SerializationContext,,)

    typedef VariableDeltaSerializer::DeserializationContext DeserializationContext;
    LM_CLASS(type_sys, DeserializationContext)
    LM_CONSTR(DeserializationContext,,)
    LM_FIELD(DeserializationContext, (bitStream))

    LM_CLASS_NO_COPY(type_sys, VariableDeltaSerializer)
    LM_FUNC(VariableDeltaSerializer,
            (BeginUnreliableAckedSerialize)(BeginUniqueSerialize)(BeginIdenticalSerialize)
            (EndSerialize)(BeginDeserialize)(EndDeserialize)
            (AddRemoteSystemVariableHistory)
            (OnPreSerializeTick)
            (OnMessageReceipt)
    )

    LM_FUNC_OVERLOAD(VariableDeltaSerializer, "RemoveRemoteSystemVariableHistory",
        RemoveRemoteSystemVariableHistory, void, RakNetGUID)


#define DefSerialize(type) \
        LM_FUNC_OVERLOAD(VariableDeltaSerializer, "SerializeVariable_" #type, SerializeVariable, void, SerializationContext*, const type &) \
        LM_FUNC_OVERLOAD(VariableDeltaSerializer, "DeserializeVariable_" #type, DeserializeVariable, bool, DeserializationContext*, type &) \
        VariableDeltaSerializer_LM.bind_nonmember_op("DeserializeVariable_" #type, &deserialize_helper<type>); \
        typedef DeserializationResult<type> DeserializationResult_##type; \
        LM_CLASS(type_sys, DeserializationResult_##type) \
        LM_FUNC_OVERLOAD_CONST(DeserializationResult_##type, "success", get_success, bool) \
        LM_FUNC_OVERLOAD_CONST(DeserializationResult_##type, "value", get_value, type)

    DefSerialize(bool)
    DefSerialize(char)
    DefSerialize(short)
    DefSerialize(int)
    DefSerialize(long)
    DefSerialize(float)
    DefSerialize(double)
    DefSerialize(NetworkID)

    typedef unsigned int uint;
    DefSerialize(uint)

	LM_CLASS_NO_COPY(type_sys, SerializeParameters)
	LM_FIELD(SerializeParameters, (messageTimestamp)(destinationConnection)(bitsWrittenSoFar)(whenLastSerialized)(curTime))
	LM_ARRAY_FIELD(SerializeParameters, (outputBitstream)(lastSentBitstream)(pro))

	LM_CLASS_NO_COPY(type_sys, DeserializeParameters)
	LM_FIELD(DeserializeParameters, (timeStamp)(sourceConnection))
	LM_ARRAY_FIELD(DeserializeParameters, (serializationBitstream)(bitstreamWrittenTo))
}

}}
