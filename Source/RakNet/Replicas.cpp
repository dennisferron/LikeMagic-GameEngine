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
#include "IoObject.h"
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

enum
{
	CLIENT,
	SERVER,
	P2P
} topology = SERVER;

// ReplicaManager3 is in the namespace RakNet
using namespace RakNet;

struct ScriptedReplicaBase : public Replica3, public MarkableObjGraph
{
protected:
	//ScriptedReplicaBase() {var1Unreliable=0; var2Unreliable=0; var3Reliable=0; var4Reliable=0;}

public:

	IoObject* io_obj;

    virtual ~ScriptedReplicaBase() {}
	virtual RakNet::RakString GetName(void) const { throw std::logic_error("Scripted Replica has no name.  Please attach a block to OnGetName."); }
	virtual void WriteAllocationID(RakNet::Connection_RM3 *destinationConnection, RakNet::BitStream *allocationIdBitstream) const {
		allocationIdBitstream->Write(GetName());
	}
	void PrintStringInBitstream(RakNet::BitStream *bs)
	{
		if (bs->GetNumberOfBitsUsed()==0)
			return;
		RakNet::RakString rakString;
		bs->Read(rakString);
		printf("Receive: %s\n", rakString.C_String());
	}

	virtual void SerializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *destinationConnection)	{

		// variableDeltaSerializer is a helper class that tracks what variables were sent to what remote system
		// This call adds another remote system to track
		variableDeltaSerializer.AddRemoteSystemVariableHistory(destinationConnection->GetRakNetGUID());

		constructionBitstream->Write(GetName() + RakNet::RakString(" SerializeConstruction"));
	}
	virtual bool DeserializeConstruction(RakNet::BitStream *constructionBitstream, RakNet::Connection_RM3 *sourceConnection) {
		PrintStringInBitstream(constructionBitstream);
		return true;
	}
	virtual void SerializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *destinationConnection)	{

		// variableDeltaSerializer is a helper class that tracks what variables were sent to what remote system
		// This call removes a remote system
		variableDeltaSerializer.RemoveRemoteSystemVariableHistory(destinationConnection->GetRakNetGUID());

		destructionBitstream->Write(GetName() + RakNet::RakString(" SerializeDestruction"));

	}
	virtual bool DeserializeDestruction(RakNet::BitStream *destructionBitstream, RakNet::Connection_RM3 *sourceConnection) {
		PrintStringInBitstream(destructionBitstream);
		return true;
	}
	virtual void DeallocReplica(RakNet::Connection_RM3 *sourceConnection) {
		delete this;
	}

	/// Overloaded Replica3 function
	virtual void OnUserReplicaPreSerializeTick(void)
	{
		/// Required by VariableDeltaSerializer::BeginIdenticalSerialize()
		variableDeltaSerializer.OnPreSerializeTick();
	}

	virtual RM3SerializationResult Serialize(SerializeParameters *serializeParameters)
	{
	    throw std::logic_error("Serialize not implemented.  Please attach a block to OnSerialize.");

        /*

		VariableDeltaSerializer::SerializationContext serializationContext;

		// Put all variables to be sent unreliably on the same channel, then specify the send type for that channel
		serializeParameters->pro[0].reliability=UNRELIABLE_WITH_ACK_RECEIPT;
		// Sending unreliably with an ack receipt requires the receipt number, and that you inform the system of ID_SND_RECEIPT_ACKED and ID_SND_RECEIPT_LOSS
		serializeParameters->pro[0].sendReceipt=replicaManager->GetRakPeerInterface()->IncrementNextSendReceipt();
		serializeParameters->messageTimestamp=RakNet::GetTime();

		// Begin writing all variables to be sent UNRELIABLE_WITH_ACK_RECEIPT
		variableDeltaSerializer.BeginUnreliableAckedSerialize(
			&serializationContext,
			serializeParameters->destinationConnection->GetRakNetGUID(),
			&serializeParameters->outputBitstream[0],
			serializeParameters->pro[0].sendReceipt
			);
		// Write each variable
		variableDeltaSerializer.SerializeVariable(&serializationContext, var1Unreliable);
		// Write each variable
		variableDeltaSerializer.SerializeVariable(&serializationContext, var2Unreliable);
		// Tell the system this is the last variable to be written
		variableDeltaSerializer.EndSerialize(&serializationContext);

		// All variables to be sent using a different mode go on different channels
		serializeParameters->pro[1].reliability=RELIABLE_ORDERED;

		// Same as above, all variables to be sent with a particular reliability are sent in a batch
		// We use BeginIdenticalSerialize instead of BeginSerialize because the reliable variables have the same values sent to all systems. This is memory-saving optimization
		variableDeltaSerializer.BeginIdenticalSerialize(
			&serializationContext,
			serializeParameters->whenLastSerialized==0,
			&serializeParameters->outputBitstream[1]
			);
		variableDeltaSerializer.SerializeVariable(&serializationContext, var3Reliable);
		variableDeltaSerializer.SerializeVariable(&serializationContext, var4Reliable);
		variableDeltaSerializer.EndSerialize(&serializationContext);

		// This return type makes is to ReplicaManager3 itself does not do a memory compare. we entirely control serialization ourselves here.
		// Use RM3SR_SERIALIZED_ALWAYS instead of RM3SR_SERIALIZED_ALWAYS_IDENTICALLY to support sending different data to different system, which is needed when using unreliable and dirty variable resends
		return RM3SR_SERIALIZED_ALWAYS;
		*/
	}
	virtual void Deserialize(RakNet::DeserializeParameters *deserializeParameters)
	{
	    throw std::logic_error("Deserialize not implemented. Please attach a script block to OnDeserialize");
	}

	virtual void SerializeConstructionRequestAccepted(RakNet::BitStream *serializationBitstream, RakNet::Connection_RM3 *requestingConnection)
	{
		serializationBitstream->Write(GetName() + RakNet::RakString(" SerializeConstructionRequestAccepted"));
	}

	virtual void DeserializeConstructionRequestAccepted(RakNet::BitStream *serializationBitstream, RakNet::Connection_RM3 *acceptingConnection)
	{
		PrintStringInBitstream(serializationBitstream);
	}

	virtual void SerializeConstructionRequestRejected(RakNet::BitStream *serializationBitstream, RakNet::Connection_RM3 *requestingConnection)
	{
		serializationBitstream->Write(GetName() + RakNet::RakString(" SerializeConstructionRequestRejected"));
	}

	virtual void DeserializeConstructionRequestRejected(RakNet::BitStream *serializationBitstream, RakNet::Connection_RM3 *rejectingConnection)
	{
		PrintStringInBitstream(serializationBitstream);
	}

	void OnPoppedConnection(RakNet::Connection_RM3 *droppedConnection)
	{
		// Same as in SerializeDestruction(), no longer track this system
		variableDeltaSerializer.RemoveRemoteSystemVariableHistory(droppedConnection->GetRakNetGUID());
	}

	void NotifyReplicaOfMessageDeliveryStatus(RakNetGUID guid, uint32_t receiptId, bool messageArrived)
	{
		// When using UNRELIABLE_WITH_ACK_RECEIPT, the system tracks which variables were updated with which sends
		// So it is then necessary to inform the system of messages arriving or lost
		// Lost messages will flag each variable sent in that update as dirty, meaning the next Serialize() call will resend them with the current values
		variableDeltaSerializer.OnMessageReceipt(guid,receiptId,messageArrived);
	}

	virtual RM3ConstructionState QueryConstruction(RakNet::Connection_RM3 *destinationConnection, ReplicaManager3 *replicaManager3)
	{
		throw std::logic_error("QueryConstruction not implemented. Please provide a script block for OnQueryConstruction.");
	}

	virtual bool QueryRemoteConstruction(RakNet::Connection_RM3 *sourceConnection)
	{
		throw std::logic_error("QueryRemoteConstruction not implemented. Please provide a script block for OnQueryRemoteConstruction.");
	}

	virtual RM3QuerySerializationResult QuerySerialization(RakNet::Connection_RM3 *destinationConnection)
	{
		throw std::logic_error("QuerySerialization not implemented. Please provide a script block for OnQuerySerialization.");
	}

	virtual RM3ActionOnPopConnection QueryActionOnPopConnection(RakNet::Connection_RM3 *droppedConnection) const
	{
		throw std::logic_error("QueryActionOnPopConnection not implemented. Please provide a script block for OnQueryActionOnPopConnection.");
	}

	/*

	void RandomizeVariables(void)
	{
		if (randomMT()%2)
		{
			var1Unreliable=randomMT();
			printf("var1Unreliable changed to %i\n", var1Unreliable);
		}
		if (randomMT()%2)
		{
			var2Unreliable=randomMT();
			printf("var2Unreliable changed to %i\n", var2Unreliable);
		}
		if (randomMT()%2)
		{
			var3Reliable=randomMT();
			printf("var3Reliable changed to %i\n", var3Reliable);
		}
		if (randomMT()%2)
		{
			var4Reliable=randomMT();
			printf("var4Reliable changed to %i\n", var4Reliable);
		}
	}

	*/

	// Demonstrate per-variable synchronization
	// We manually test each variable to the last synchronized value and only send those values that change
	//int var1Unreliable,var2Unreliable,var3Reliable,var4Reliable;

	// Class to save and compare the states of variables this Serialize() to the last Serialize()
	// If the value is different, true is written to the bitStream, followed by the value. Otherwise false is written.
	// It also tracks which variables changed which Serialize() call, so if an unreliable message was lost (ID_SND_RECEIPT_LOSS) those variables are flagged 'dirty' and resent
	VariableDeltaSerializer variableDeltaSerializer;
};

#include "boost/preprocessor/control/iif.hpp"

#define TypedArgList(r, data, i, elem) BOOST_PP_COMMA_IF(i) elem data##i

// Example:  ScriptFunc(0, MyRetType, FuncName, const, 3, ClassX, ClassY, ClassZ)
// Expands to: IoBlock On##FuncName; MyRetType FuncName(ClassX arg0, ClassY arg1, ClassZ arg2) const { ... }
//
#define ScriptFunc(IsVoid, RType, FuncName, CONST, ArgTypes) \
IoBlock On##FuncName; \
virtual RType FuncName( \
    BOOST_PP_SEQ_FOR_EACH_I(TypedArgList, arg, ArgTypes) \
) CONST \
{ \
    if (On##FuncName.empty()) \
        BOOST_PP_IIF(IsVoid, , return) Base::FuncName(BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ArgTypes), arg)); \
    else \
        BOOST_PP_IIF(IsVoid, , return) On##FuncName.eval<RType>(BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ArgTypes), arg)); \
}

struct ScriptedReplica : public ScriptedReplicaBase
{
	//ScriptedReplica() {var1Unreliable=0; var2Unreliable=0; var3Reliable=0; var4Reliable=0;}
	~ScriptedReplica() {}

	RM3SerializationResult BaseSerialize(SerializeParameters *serializeParameters)
	{
	    return ScriptedReplicaBase::Serialize(serializeParameters);
	}

    // For the ScriptFunc macros
    typedef ScriptedReplicaBase Base;
    ScriptFunc(0, RakString, GetName,                   const,      )
    ScriptFunc(1, void, WriteAllocationID,              const,  (RakNet::Connection_RM3*)(RakNet::BitStream*))
    ScriptFunc(1, void, SerializeConstruction,          ,       (RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(0, bool, DeserializeConstruction,        ,       (RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(1, void, SerializeDestruction,           ,       (RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(0, bool, DeserializeDestruction,         ,       (RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(1, void, DeallocReplica,                 ,       (RakNet::Connection_RM3*))
    ScriptFunc(1, void, OnUserReplicaPreSerializeTick,  ,           )
    ScriptFunc(0, RM3SerializationResult, Serialize,    ,       (SerializeParameters*))
    ScriptFunc(1, void, Deserialize,                    ,       (RakNet::DeserializeParameters*))
    ScriptFunc(1, void, SerializeConstructionRequestAccepted,,  (RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(1, void, DeserializeConstructionRequestAccepted,,(RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(1, void, SerializeConstructionRequestRejected,,  (RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(1, void, DeserializeConstructionRequestRejected,,(RakNet::BitStream*)(RakNet::Connection_RM3*))
    ScriptFunc(1, void, OnPoppedConnection,             ,       (RakNet::Connection_RM3*))
    ScriptFunc(1, void, NotifyReplicaOfMessageDeliveryStatus,,  (RakNetGUID)(uint32_t)(bool))

    ScriptFunc(0, RM3ConstructionState, QueryConstruction,,     (RakNet::Connection_RM3*)(ReplicaManager3*))
	ScriptFunc(0, bool, QueryRemoteConstruction,        ,       (RakNet::Connection_RM3*))
	ScriptFunc(0, RM3QuerySerializationResult, QuerySerialization,,             (RakNet::Connection_RM3*))
	ScriptFunc(0, RM3ActionOnPopConnection, QueryActionOnPopConnection, const,  (RakNet::Connection_RM3*))
};


class ScriptedConnection : public Connection_RM3, public MarkableObjGraph
{
public:
	ScriptedConnection(SystemAddress _systemAddress, RakNetGUID _guid) : Connection_RM3(_systemAddress, _guid) {}
	virtual ~ScriptedConnection() {}

	// See documentation - Makes all messages between ID_REPLICA_MANAGER_DOWNLOAD_STARTED and ID_REPLICA_MANAGER_DOWNLOAD_COMPLETE arrive in one tick
	bool QueryGroupDownloadMessages(void) const
	{
	    if (OnQueryGroupDownloadMessages.empty())
            return true;
        else
            return OnQueryGroupDownloadMessages.eval<bool>();
    }

	virtual Replica3 *AllocReplica(RakNet::BitStream *allocationId, ReplicaManager3 *replicaManager3)
	{
	    Replica3* result = OnAllocReplica.eval<Replica3*>(allocationId, replicaManager3);
	    add_mark_obj(result);
	    return result;
	}

public:
    IoBlock OnQueryGroupDownloadMessages;
    IoBlock OnAllocReplica;
    IoBlock OnTest;
};

class ScriptedReplicaManager3 : public ReplicaManager3, public MarkableObjGraph
{
protected:
	virtual Connection_RM3* AllocConnection(SystemAddress systemAddress, RakNetGUID rakNetGUID) const {
		//return new ScriptedConnection(systemAddress,rakNetGUID);
		Connection_RM3* result = OnAllocConnection.eval<Connection_RM3*>(systemAddress, rakNetGUID);
		add_mark_obj(result);
		return result;
	}
	virtual void DeallocConnection(Connection_RM3 *connection) const {
		//delete connection;
		OnDeallocConnection(connection);
		remove_mark_obj(connection);
	}

public:
    IoBlock OnAllocConnection;
    IoBlock OnDeallocConnection;
};


namespace Bindings { namespace RakNet {


void add_bindings_replicas(RuntimeTypeSystem& type_sys)
{
    LM_CLASS(type_sys, NetworkIDManager)
    LM_CONSTR(NetworkIDManager,,)
    LM_FUNC_OVERLOAD(NetworkIDManager, "GET_OBJECT_FROM_ID_ScriptedReplica", GET_OBJECT_FROM_ID, ScriptedReplica*, NetworkID)
    LM_FUNC_OVERLOAD(NetworkIDManager, "GET_OBJECT_FROM_ID_IoObject", GET_OBJECT_FROM_ID, IoObject*, NetworkID)

    LM_CLASS(type_sys, PluginInterface2)
    LM_FUNC(PluginInterface2, (GetRakPeerInterface))

    LM_CLASS(type_sys, ReplicaManager3)
    LM_BASE(ReplicaManager3, PluginInterface2)
    LM_FUNC(ReplicaManager3, (SetNetworkIDManager)(GetReplicasCreatedByMe)(Reference)(BroadcastDestructionList))

    LM_CLASS(type_sys, RM3SerializationResult)
    LM_CLASS(type_sys, RM3ConstructionState)
	LM_CLASS(type_sys, RM3QuerySerializationResult)
	LM_CLASS(type_sys, RM3ActionOnPopConnection)

    LM_CLASS(type_sys, ScriptedReplicaManager3)
    LM_BASE(ScriptedReplicaManager3, ReplicaManager3)
    LM_CONSTR(ScriptedReplicaManager3,,)
    LM_FIELD(ScriptedReplicaManager3, (OnAllocConnection)(OnDeallocConnection))

    LM_CLASS(type_sys, Connection_RM3)
    LM_FUNC(Connection_RM3, (GetRakNetGUID))

    LM_CLASS(type_sys, ScriptedConnection)
    LM_BASE(ScriptedConnection, Connection_RM3)
    LM_CONSTR(ScriptedConnection,, SystemAddress, RakNetGUID)
    LM_FIELD(ScriptedConnection, (OnAllocReplica)(OnQueryGroupDownloadMessages)(OnTest))

    LM_CLASS_NO_COPY(type_sys, NetworkIDObject)
    LM_FUNC(NetworkIDObject, (SetNetworkIDManager)(GetNetworkIDManager)(GetNetworkID)(SetNetworkID)(SetParent)(GetParent))

    LM_CLASS_NO_COPY(type_sys, Replica3)
    LM_BASE(Replica3, NetworkIDObject)
    LM_FUNC(Replica3,
        (QueryConstruction_ClientConstruction)
        (QueryConstruction_ServerConstruction)
        (QueryRemoteConstruction_ClientConstruction)
        (QueryRemoteConstruction_ServerConstruction)
        (QuerySerialization_ClientSerializable)
        (QuerySerialization_ServerSerializable)
        (QueryActionOnPopConnection_Client)
        (QueryActionOnPopConnection_Server)
        (Serialize)
    )

    LM_CLASS_NO_COPY(type_sys, ScriptedReplicaBase)
    LM_BASE(ScriptedReplicaBase, Replica3)
    LM_FIELD(ScriptedReplicaBase, (variableDeltaSerializer))
    LM_FUNC(ScriptedReplicaBase, (PrintStringInBitstream))

    LM_CLASS_NO_COPY(type_sys, ScriptedReplica)
    LM_BASE(ScriptedReplica, ScriptedReplicaBase)
    LM_CONSTR(ScriptedReplica,,)
    LM_FUNC(ScriptedReplica, (BaseSerialize))
    LM_FIELD(ScriptedReplica,
        (OnGetName)
        (OnWriteAllocationID)
        (OnSerializeConstruction)
        (OnDeserializeConstruction)
        (OnSerializeDestruction)
        (OnDeserializeDestruction)
        (OnDeallocReplica)
        (OnOnUserReplicaPreSerializeTick)
        (OnSerialize)
        (OnDeserialize)
        (OnSerializeConstructionRequestAccepted)
        (OnDeserializeConstructionRequestAccepted)
        (OnSerializeConstructionRequestRejected)
        (OnDeserializeConstructionRequestRejected)
        (OnOnPoppedConnection)
        (OnNotifyReplicaOfMessageDeliveryStatus)
        (OnQueryConstruction)
        (OnQueryRemoteConstruction)
        (OnQuerySerialization)
        (OnQueryActionOnPopConnection)
    )
}

}}
