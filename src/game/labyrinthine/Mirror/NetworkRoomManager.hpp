#pragma once
#include "../base/List.hpp"
#include "../base/String.hpp"
#include "NetworkManager.hpp"
#include "NetworkRoomPlayer.hpp"

namespace YimMenu
{
	class NetworkRoomManager : public Mirror_NetworkManager_o
	{
    public:
		bool showRoomGUI;
		int32_t minPlayers;
		Mirror_NetworkRoomPlayer_o* roomPlayerPrefab;
		String* RoomScene;
		String* GameplayScene;
		struct System_Collections_Generic_HashSet_NetworkRoomManager_PendingPlayer__o* pendingPlayers;
		bool _allPlayersReady;
		struct System_Collections_Generic_HashSet_NetworkRoomPlayer__o* roomSlots;
		int32_t clientIndex;
	};
	static_assert(sizeof(NetworkRoomManager) == 0xF0);
}
