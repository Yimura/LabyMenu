#pragma once
#include "PlayerNetworkSync.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "base/List.hpp"

namespace YimMenu
{
	class GameManager_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		struct ValkoGames_Labyrinthine_SpawnpointsManager_o* spawnpointsManager;
		bool spawnNetworkObjects;
		struct UnityEngine_GameObject_o* mainPlayer;
		List<PlayerNetworkSync_o*>* alivePlayers;
		List<PlayerNetworkSync_o*>* players;
		Array<PlayerNetworkSync_o*>* playersOrdered;
		bool canRespawn;
		bool spawnCryptGates;
		struct UnityEngine_Transform_o* cryptGateHolder;
	};
	static_assert(sizeof(GameManager_o) == 0x60);

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct GameManager_VTable
	{
		// _0_Equals
		VTableSlot<bool(Il2CppObject*)>     Equals;
		// _1_Finalize
		VTableSlot<void()>                  Finalize;
		// _2_GetHashCode
		VTableSlot<int32_t()>               GetHashCode;
		// _3_ToString
		VTableSlot<System_String_o*()>      ToString;
	};

	struct GameManager_StaticFields
	{
		GameManager_o* instance;
	};

	struct GameManager_c
	{
		Il2CppClass_1 _1;
		GameManager_StaticFields* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		GameManager_VTable vtable;
	};
}
