#pragma once
#include "PlayerNetworkSync.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "base/List.hpp"
#include "il2cpp/il2cpp.hpp"

namespace YimMenu
{
	class GameManager_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		struct ValkoGames_Labyrinthine_SpawnpointsManager_o* spawnpointsManager;
		bool spawnNetworkObjects;
		struct UnityEngine_GameObject_o* mainPlayer;
		const List<PlayerNetworkSync_o>* alivePlayers;
		const List<PlayerNetworkSync_o>* players;
		Array<PlayerNetworkSync_o>* playersOrdered;
		bool canRespawn;
		bool spawnCryptGates;
		struct UnityEngine_Transform_o* cryptGateHolder;
	};
	static_assert(sizeof(GameManager_o) == 0x58);
}
