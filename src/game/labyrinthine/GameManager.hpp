#pragma once
#include "PlayerNetworkSync.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "base/List.hpp"
#include "il2cpp/il2cpp.hpp"

namespace YimMenu
{
	class GameManager_Fields : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		struct ValkoGames_Labyrinthine_SpawnpointsManager_o* spawnpointsManager;
		bool spawnNetworkObjects;
		struct UnityEngine_GameObject_o* mainPlayer;
		List<PlayerNetworkSync_o>* alivePlayers;
		List<PlayerNetworkSync_o>* players;
		Array<PlayerNetworkSync_o>* playersOrdered;
		bool canRespawn;
		bool spawnCryptGates;
		struct UnityEngine_Transform_o* cryptGateHolder;
	};
	static_assert(sizeof(GameManager_Fields) == 0x48);

	class GameManager_c;
	class GameManager_o
	{
	public:
		GameManager_c* klass;
		void* monitor;
		GameManager_Fields fields;
	};


	class GameManager_c
	{
	public:
		Il2CppClass_1 _1;
		GameManager_o** static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		void* vtable;
	};
}
