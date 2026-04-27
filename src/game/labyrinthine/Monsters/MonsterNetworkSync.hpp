#pragma once
#include "../Mirror/NetworkBehaviour.hpp"
#include "../UnityEngine/Quaternion.hpp"
#include "../UnityEngine/Vector3.hpp"

#include <cstdint>

namespace YimMenu
{
	class AIController_o;

	// MonsterNetworkSync is the shared base for every AI-driven monster
	// (Bat/Spider/Clown/...) that's network-replicated. Field offsets verified
	// against reversing/dump.cs (TypeDefIndex 2399).
	class MonsterNetworkSync_o : public Mirror_NetworkBehaviour_Fields
	{
	public:
		struct ValkoGames_Labyrinthine_Data_FloatSO_o*  posSyncInterval;                  // 0x68
		struct ValkoGames_Labyrinthine_Data_FloatSO_o*  maxInterpolationTime;             // 0x70
		struct ValkoGames_Labyrinthine_Data_FloatSO_o*  killSequenceEndMaxPositionDiff;   // 0x78
		struct ValkoGames_Labyrinthine_Data_FloatSO_o*  killSequenceWaitingTimeout;       // 0x80
		struct ValkoGames_Labyrinthine_Data_FloatSO_o*  killVisionRaycastDistance;        // 0x88
		struct ValkoGames_Labyrinthine_Data_LayerMaskSO_o* killVisionRaycastMask;         // 0x90
		struct System_Collections_Generic_List_EventWithKey__o* remoteEvents;             // 0x98
		struct System_String_o*                          chaseEventKey;                   // 0xA0
		struct UnityEngine_Animator_o*                   m_Animator;                      // 0xA8
		struct ValkoGames_Labyrinthine_Monsters_MonsterAnimationHandler_o* m_MonsterAnimationHandler; // 0xB0
		int32_t                                          _CurrentAnimationState_k__BackingField; // 0xB8 (AnimationState enum)
		uint8_t                                          _pad_BC[4];                      // 0xBC alignment
		AIController_o*                                  _AIController_k__BackingField;   // 0xC0
		bool                                             isEnabled;                       // 0xC8 (SyncVar)
		bool                                             _IsChasingPlayer_k__BackingField;// 0xC9 — universal "actively hunting" flag
		uint8_t                                          monsterID;                       // 0xCA (SyncVar)
		uint8_t                                          currentEventState;               // 0xCB (SyncVar)
		float                                            syncTimer;                       // 0xCC
		float                                            interpolationTimer;              // 0xD0
		Vector3                                          position;                        // 0xD4 (synced world position)
		Vector3                                          lastRemotePosition;              // 0xE0
		Quaternion                                       rotation;                        // 0xEC (16 bytes)
		Quaternion                                       lastRemoteRotation;              // 0xFC
		bool                                             isInterpolationPaused;           // 0x10C
		bool                                             serverIsStunned;                 // 0x10D
		uint8_t                                          _pad_10E[2];                     // 0x10E alignment
		struct System_Collections_Generic_Dictionary_string__byte__o* remoteEventsKeyCache; // 0x110
		struct UnityEngine_Coroutine_o*                  stunCoroutine;                   // 0x118
		struct System_Delegate_o*                        AnimationStateChanged;           // 0x120
		struct System_Delegate_o*                        ServerPlayerKilled;              // 0x128
		struct System_Delegate_o*                        ServerPlayerChaseStarted;        // 0x130
		struct System_Delegate_o*                        _Mirror_SyncVarHookDelegate_currentEventState; // 0x138
	};
	static_assert(sizeof(MonsterNetworkSync_o) == 0x140);
	static_assert(offsetof(MonsterNetworkSync_o, _AIController_k__BackingField) == 0xC0);
	static_assert(offsetof(MonsterNetworkSync_o, _IsChasingPlayer_k__BackingField) == 0xC9);
	static_assert(offsetof(MonsterNetworkSync_o, position) == 0xD4);

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct MonsterNetworkSync_VTable
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
		// _18_OnUpdate
		VTableSlot<void()>                                             OnUpdate;
		// _19_ShouldCheckCollision
		VTableSlot<void()>                                             ShouldCheckCollision;
		// _20_CanKillPlayer
		VTableSlot<void()>                                             CanKillPlayer;
		// _21_ServerWriteSyncData
		VTableSlot<void()>                                             ServerWriteSyncData;
		// _22_ReadSyncData
		VTableSlot<void()>                                             ReadSyncData;
		// _23_OnKillSequenceStart
		VTableSlot<void()>                                             OnKillSequenceStart;
		// _24_OnKillSequenceEnd
		VTableSlot<void()>                                             OnKillSequenceEnd;
		// _25_ServerOnStartKillSequence
		VTableSlot<void()>                                             ServerOnStartKillSequence;
		// _26_ServerCanBeStunned
		VTableSlot<void()>                                             ServerCanBeStunned;
		// _27_ServerStunCoroutine
		VTableSlot<void()>                                             ServerStunCoroutine;
	};

	struct MonsterNetworkSync_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		MonsterNetworkSync_VTable vtable;
	};
}
