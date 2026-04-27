#pragma once
#include "../UnityEngine/MonoBehaviour.hpp"
#include "../base/List.hpp"
#include "../base/String.hpp"
#include "../il2cpp/il2cpp.hpp"

#include <cstdint>

namespace YimMenu
{
	class Mirror_NetworkConnection_o;

	class Mirror_NetworkManager_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		bool dontDestroyOnLoad;
		bool runInBackground;
		int32_t headlessStartMode;
		bool editorAutoStart;
		int32_t sendRate;
		String* offlineScene;
		String* onlineScene;
		float offlineSceneLoadDelay;
		struct Mirror_Transport_o* transport;
		String* networkAddress;
		int32_t maxConnections;
		bool disconnectInactiveConnections;
		float disconnectInactiveTimeout;
		struct Mirror_NetworkAuthenticator_o* authenticator;
		struct UnityEngine_GameObject_o* playerPrefab;
		bool autoCreatePlayer;
		int32_t playerSpawnMethod;
		List<void*>* spawnPrefabs;
		bool exceptionsDisconnect;
		struct Mirror_SnapshotInterpolationSettings_o* snapshotSettings;
		uint8_t evaluationMethod;
		float evaluationInterval;
		bool timeInterpolationGui;
		bool clientLoadedScene;
		int32_t _mode_k__BackingField;
		bool finishStartHostPending;
		uint8_t clientSceneOperation;
	};
	static_assert(sizeof(Mirror_NetworkManager_o) == 0xB0);

	// Slots 0-3: System.Object base. 4-12: Unity lifecycle. 13-22: server-side.
	// 23-29: client-side. 30-35: host/start/stop. Most return void; signatures
	// for connection-taking slots use Mirror_NetworkConnection_o (Mirror's
	// NetworkConnectionToClient inherits from it).
	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct Mirror_NetworkManager_VTable
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
	};

	struct Mirror_NetworkManager_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		Mirror_NetworkManager_VTable vtable;
	};
}
