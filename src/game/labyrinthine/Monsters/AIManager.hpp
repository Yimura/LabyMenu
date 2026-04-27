#pragma once
#include "../UnityEngine/MonoBehaviour.hpp"
#include "../base/List.hpp"
#include "AIController.hpp"

#include <cstdint>

namespace YimMenu
{
	// AIManager is the static singleton that tracks every spawned AIController
	// across all monster types. Field offsets verified against
	// reversing/dump.cs (TypeDefIndex 2316).
	class AIManager_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		float                                          maxWaypointDistance;             // 0x20
		float                                          ignorePlayerDuration;            // 0x24
		struct System_Collections_Generic_List_PlayerNetworkSync__o* ignoredPlayers;    // 0x28
		struct System_Collections_Generic_List_AIPatrolPoint__o*     allWaypoints;      // 0x30
		struct System_Collections_Generic_Dictionary_MonsterType__SharedTransformList__o* aiPatrolPoints; // 0x38
		struct System_Collections_Generic_Dictionary_MonsterType__List_AIController___o* aiControllers; // 0x40
		List<AIController_o*>*                         allAIControllers;                // 0x48 — what we iterate
		struct System_Collections_Generic_Dictionary_Transform__AIController__o* waypointsState; // 0x50
	};
	static_assert(sizeof(AIManager_o) == 0x58);
	static_assert(offsetof(AIManager_o, allAIControllers) == 0x48);

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct AIManager_VTable
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
	};

	struct AIManager_StaticFields
	{
		AIManager_o* instance;
	};

	struct AIManager_c
	{
		Il2CppClass_1 _1;
		AIManager_StaticFields* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		AIManager_VTable vtable;
	};
}
