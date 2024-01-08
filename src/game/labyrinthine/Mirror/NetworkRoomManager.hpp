#pragma once
#include "../base/List.hpp"
#include "../base/String.hpp"
#include "NetworkManager.hpp"
#include "NetworkRoomPlayer.hpp"

namespace YimMenu
{
	class Mirror_NetworkRoomManager_Fields : public Mirror_NetworkManager_Fields
	{
    public:
		bool showRoomGUI;
		int32_t minPlayers;
		Mirror_NetworkRoomPlayer_o* roomPlayerPrefab;
		String* RoomScene;
		String* GameplayScene;
		struct System_Collections_Generic_List_NetworkRoomManager_PendingPlayer__o* pendingPlayers;
		bool _allPlayersReady;
		List<Mirror_NetworkRoomPlayer_o>* roomSlots;
		int32_t clientIndex;
	};

	struct Mirror_NetworkRoomManager_o
	{
		void* klass;
		void* monitor;
		Mirror_NetworkRoomManager_Fields fields;
	};
}
