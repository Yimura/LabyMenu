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

	// First 36 slots match Mirror_NetworkManager_VTable. Slots 36+ are
	// NetworkRoomManager-specific; signatures default to void() — refine when
	// invoking. The OnRoomServerCreate*/OnRoomServerSceneLoadedForPlayer slots
	// take an Mirror_NetworkConnection_o*, etc.
	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct Mirror_NetworkRoomManager_VTable
	{
		// _0_Equals
		VTableSlot<bool(Il2CppObject*)>                                  Equals;
		// _1_Finalize
		VTableSlot<void()>                                               Finalize;
		// _2_GetHashCode
		VTableSlot<int32_t()>                                            GetHashCode;
		// _3_ToString
		VTableSlot<System_String_o*()>                                   ToString;
		// _4_OnValidate
		VTableSlot<void()>                                               OnValidate;
		// _5_Reset
		VTableSlot<void()>                                               Reset;
		// _6_Awake
		VTableSlot<void()>                                               Awake;
		// _7_Start
		VTableSlot<void()>                                               Start;
		// _8_Update
		VTableSlot<void()>                                               Update;
		// _9_LateUpdate
		VTableSlot<void()>                                               LateUpdate;
		// _10_OnApplicationQuit
		VTableSlot<void()>                                               OnApplicationQuit;
		// _11_ConfigureHeadlessFrameRate
		VTableSlot<void()>                                               ConfigureHeadlessFrameRate;
		// _12_OnDestroy
		VTableSlot<void()>                                               OnDestroy;
		// _13_ServerChangeScene
		VTableSlot<void(System_String_o*)>                               ServerChangeScene;
		// _14_GetStartPosition
		VTableSlot<struct UnityEngine_Transform_o*()>                    GetStartPosition;
		// _15_OnServerConnect
		VTableSlot<void(Mirror_NetworkConnection_o*)>                    OnServerConnect;
		// _16_OnServerDisconnect
		VTableSlot<void(Mirror_NetworkConnection_o*)>                    OnServerDisconnect;
		// _17_OnServerReady
		VTableSlot<void(Mirror_NetworkConnection_o*)>                    OnServerReady;
		// _18_OnServerAddPlayer
		VTableSlot<void(Mirror_NetworkConnection_o*)>                    OnServerAddPlayer;
		// _19_OnServerError
		VTableSlot<void(Mirror_NetworkConnection_o*, int32_t, System_String_o*)> OnServerError;
		// _20_OnServerTransportException
		VTableSlot<void(Mirror_NetworkConnection_o*, void*)>             OnServerTransportException;
		// _21_OnServerChangeScene
		VTableSlot<void(System_String_o*)>                               OnServerChangeScene;
		// _22_OnServerSceneChanged
		VTableSlot<void(System_String_o*)>                               OnServerSceneChanged;
		// _23_OnClientConnect
		VTableSlot<void()>                                               OnClientConnect;
		// _24_OnClientDisconnect
		VTableSlot<void()>                                               OnClientDisconnect;
		// _25_OnClientError
		VTableSlot<void(int32_t, System_String_o*)>                      OnClientError;
		// _26_OnClientTransportException
		VTableSlot<void(void*)>                                          OnClientTransportException;
		// _27_OnClientNotReady
		VTableSlot<void()>                                               OnClientNotReady;
		// _28_OnClientChangeScene
		VTableSlot<void(System_String_o*, int32_t, bool)>                OnClientChangeScene;
		// _29_OnClientSceneChanged
		VTableSlot<void()>                                               OnClientSceneChanged;
		// _30_OnStartHost
		VTableSlot<void()>                                               OnStartHost;
		// _31_OnStartServer
		VTableSlot<void()>                                               OnStartServer;
		// _32_OnStartClient
		VTableSlot<void()>                                               OnStartClient;
		// _33_OnStopServer
		VTableSlot<void()>                                               OnStopServer;
		// _34_OnStopClient
		VTableSlot<void()>                                               OnStopClient;
		// _35_OnStopHost
		VTableSlot<void()>                                               OnStopHost;
		// _36_OnRoomStartHost
		VTableSlot<void()>                                               OnRoomStartHost;
		// _37_OnRoomStopHost
		VTableSlot<void()>                                               OnRoomStopHost;
		// _38_OnRoomStartServer
		VTableSlot<void()>                                               OnRoomStartServer;
		// _39_OnRoomStopServer
		VTableSlot<void()>                                               OnRoomStopServer;
		// _40_OnRoomServerConnect
		VTableSlot<void(Mirror_NetworkConnection_o*)>                    OnRoomServerConnect;
		// _41_OnRoomServerDisconnect
		VTableSlot<void(Mirror_NetworkConnection_o*)>                    OnRoomServerDisconnect;
		// _42_OnRoomServerSceneChanged
		VTableSlot<void(System_String_o*)>                               OnRoomServerSceneChanged;
		// _43_OnRoomServerCreateRoomPlayer
		VTableSlot<void()>                                               OnRoomServerCreateRoomPlayer;
		// _44_OnRoomServerCreateGamePlayer
		VTableSlot<void()>                                               OnRoomServerCreateGamePlayer;
		// _45_OnRoomServerAddPlayer
		VTableSlot<bool(Mirror_NetworkConnection_o*, struct UnityEngine_GameObject_o*)> OnRoomServerAddPlayer;
		// _46_OnRoomServerSceneLoadedForPlayer
		VTableSlot<bool(Mirror_NetworkConnection_o*, struct UnityEngine_GameObject_o*)> OnRoomServerSceneLoadedForPlayer;
		// _47_ReadyStatusChanged
		VTableSlot<void()>                                               ReadyStatusChanged;
		// _48_OnRoomServerPlayersReady
		VTableSlot<void()>                                               OnRoomServerPlayersReady;
		// _49_OnRoomServerPlayersNotReady
		VTableSlot<void()>                                               OnRoomServerPlayersNotReady;
		// _50_OnRoomClientEnter
		VTableSlot<void()>                                               OnRoomClientEnter;
		// _51_OnRoomClientExit
		VTableSlot<void()>                                               OnRoomClientExit;
		// _52_OnRoomClientConnect
		VTableSlot<void()>                                               OnRoomClientConnect;
		// _53_OnRoomClientDisconnect
		VTableSlot<void()>                                               OnRoomClientDisconnect;
		// _54_OnRoomStartClient
		VTableSlot<void()>                                               OnRoomStartClient;
		// _55_OnRoomStopClient
		VTableSlot<void()>                                               OnRoomStopClient;
		// _56_OnRoomClientSceneChanged
		VTableSlot<void(System_String_o*)>                               OnRoomClientSceneChanged;
		// _57_OnGUI
		VTableSlot<void()>                                               OnGUI;
	};

	struct Mirror_NetworkRoomManager_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		Mirror_NetworkRoomManager_VTable vtable;
	};
}
