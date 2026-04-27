#pragma once
#include "../UnityEngine/MonoBehaviour.hpp"

#include <cstdint>

namespace YimMenu
{
	class MonsterNetworkSync_o;

	// AIController sits on the same GameObject as a MonsterNetworkSync; the
	// two reference each other directly. Field offsets verified against
	// reversing/dump.cs (TypeDefIndex 2313).
	class AIController_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		int32_t  ignoredSafezones;                                    // 0x20 (SafezoneType enum)
		int32_t  monsterType;                                          // 0x24 (MonsterType enum — int-backed)
		bool     startAIOnEnable;                                      // 0x28
		bool     switchNavMeshAgentIDInRandomMode;                     // 0x29
		uint8_t  _pad_2A[6];                                           // 0x2A alignment
		struct UnityEngine_Transform_o*           overrideWaypointsParent; // 0x30
		struct BehaviorDesigner_Runtime_SharedGameObject_o* _Target_k__BackingField; // 0x38
		struct BehaviorDesigner_Runtime_BehaviorTree_o*     _BehaviorTree_k__BackingField; // 0x40
		MonsterNetworkSync_o*                     _MonsterNetworkSync_k__BackingField; // 0x48 — backref to the sync component
		struct UnityEngine_AI_NavMeshAgent_o*     _NavMeshAgent_k__BackingField;       // 0x50
		struct UnityEngine_Collider_o*            _Collider_k__BackingField;           // 0x58
		bool                                      _isEnabled;                          // 0x60
		uint8_t                                   _pad_61[7];                          // 0x61 alignment
		struct System_Delegate_o*                 OnAIStateUpdate;                     // 0x68
	};
	static_assert(sizeof(AIController_o) == 0x70);
	static_assert(offsetof(AIController_o, monsterType) == 0x24);
	static_assert(offsetof(AIController_o, _MonsterNetworkSync_k__BackingField) == 0x48);

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct AIController_VTable
	{
		// _0_Equals
		VTableSlot<bool(Il2CppObject*)>     Equals;
		// _1_Finalize
		VTableSlot<void()>                  Finalize;
		// _2_GetHashCode
		VTableSlot<int32_t()>               GetHashCode;
		// _3_ToString
		VTableSlot<System_String_o*()>      ToString;
		// _4_Awake
		VTableSlot<void()>                  Awake;
		// _5_Start
		VTableSlot<void()>                  Start;
		// _6_StartAI
		VTableSlot<void()>                  StartAI;
		// _7_GetWaypoints
		VTableSlot<void()>                  GetWaypoints;
		// _8_ApplyWaypoints
		VTableSlot<void()>                  ApplyWaypoints;
		// _9_StopAI
		VTableSlot<void()>                  StopAI;
	};

	struct AIController_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		AIController_VTable vtable;
	};
}
