#pragma once
#include "../UnityEngine/MonoBehaviour.hpp"

namespace YimMenu
{
	struct Mirror_NetworkReader_o;
	struct Mirror_NetworkWriter_o;

	class Mirror_NetworkBehaviour_Fields : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		int32_t syncDirection;
		int32_t syncMode;
		float syncInterval;
		double lastSyncTime;
		struct System_Collections_Generic_List_SyncObject__o *syncObjects;
		struct Mirror_NetworkIdentity_o *_netIdentity_k__BackingField;
		uint8_t _ComponentIndex_k__BackingField;
		uint64_t syncVarDirtyBits;
		uint64_t syncObjectDirtyBits;
		uint64_t syncVarHookGuard;
	};
	static_assert(sizeof(Mirror_NetworkBehaviour_Fields) == 0x68);

	// VTable signatures track Mirror's NetworkBehaviour API. OnSerialize/
	// SerializeSyncVars return bool in Mirror; OnDeserialize/DeserializeSyncVars
	// are void. Refine others against the dump if you invoke them.
	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct Mirror_NetworkBehaviour_VTable
	{
		// _0_Equals
		VTableSlot<bool(Il2CppObject*)>                                Equals;
		// _1_Finalize
		VTableSlot<void()>                                             Finalize;
		// _2_GetHashCode
		VTableSlot<int32_t()>                                          GetHashCode;
		// _3_ToString
		VTableSlot<System_String_o*()>                                 ToString;
		// _4_OnValidate
		VTableSlot<void()>                                             OnValidate;
		// _5_OnSerialize
		VTableSlot<bool(Mirror_NetworkWriter_o*, bool)>                OnSerialize;
		// _6_OnDeserialize
		VTableSlot<void(Mirror_NetworkReader_o*, bool)>                OnDeserialize;
		// _7_SerializeSyncVars
		VTableSlot<bool(Mirror_NetworkWriter_o*, bool)>                SerializeSyncVars;
		// _8_DeserializeSyncVars
		VTableSlot<void(Mirror_NetworkReader_o*, bool)>                DeserializeSyncVars;
		// _9_OnStartServer
		VTableSlot<void()>                                             OnStartServer;
		// _10_OnStopServer
		VTableSlot<void()>                                             OnStopServer;
		// _11_OnStartClient
		VTableSlot<void()>                                             OnStartClient;
		// _12_OnStopClient
		VTableSlot<void()>                                             OnStopClient;
		// _13_OnStartLocalPlayer
		VTableSlot<void()>                                             OnStartLocalPlayer;
		// _14_OnStopLocalPlayer
		VTableSlot<void()>                                             OnStopLocalPlayer;
		// _15_OnStartAuthority
		VTableSlot<void()>                                             OnStartAuthority;
		// _16_OnStopAuthority
		VTableSlot<void()>                                             OnStopAuthority;
		// _17_Weaved
		VTableSlot<void()>                                             Weaved;
	};

	struct Mirror_NetworkBehaviour_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		Mirror_NetworkBehaviour_VTable vtable;
	};
}
