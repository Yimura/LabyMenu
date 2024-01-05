#pragma once
#include <cstdint>
#include "../il2cpp/il2cpp.hpp"

namespace YimMenu
{
    class UnityEngine_Object_Fields
    {
        void* m_CachedPtr;
    };

    class UnityEngine_Component_Fields : UnityEngine_Object_Fields
    {
    };

    class UnityEngine_Behaviour_Fields : UnityEngine_Component_Fields
    { };

    class UnityEngine_MonoBehaviour_Fields : UnityEngine_Behaviour_Fields
    { };

    class Mirror_NetworkManager_Fields : UnityEngine_MonoBehaviour_Fields
    {
    public:
        bool dontDestroyOnLoad;
        bool runInBackground;
        bool autoStartServerBuild;
        bool showDebugMessages;
        int32_t serverTickRate;
        struct System_String_o *offlineScene;
        struct System_String_o *onlineScene;
        struct Mirror_Transport_o *transport;
        struct System_String_o *networkAddress;
        int32_t maxConnections;
        bool disconnectInactiveConnections;
        float disconnectInactiveTimeout;
        struct Mirror_NetworkAuthenticator_o *authenticator;
        struct UnityEngine_GameObject_o *playerPrefab;
        bool autoCreatePlayer;
        int32_t playerSpawnMethod;
        struct System_Collections_Generic_List_GameObject__o *spawnPrefabs;
        bool isNetworkActive;
        bool clientLoadedScene;
        int32_t _mode_k__BackingField;
        bool finishStartHostPending;
        uint8_t clientSceneOperation;
    };

    using VirtualInvokeData = void(*);
    struct Mirror_NetworkManager_VTable
    {
        VirtualInvokeData Equals;
        VirtualInvokeData Finalize;
        VirtualInvokeData GetHashCode;
        VirtualInvokeData ToString;
        VirtualInvokeData OnValidate;
        VirtualInvokeData Awake;
        VirtualInvokeData Start;
        VirtualInvokeData LateUpdate;
        VirtualInvokeData OnApplicationQuit;
        VirtualInvokeData ConfigureServerFrameRate;
        VirtualInvokeData OnDestroy;
        VirtualInvokeData ServerChangeScene;
        VirtualInvokeData OnServerConnect;
        VirtualInvokeData OnServerDisconnect;
        VirtualInvokeData OnServerReady;
        VirtualInvokeData OnServerAddPlayer;
        VirtualInvokeData OnServerError;
        VirtualInvokeData OnServerChangeScene;
        VirtualInvokeData OnServerSceneChanged;
        VirtualInvokeData OnClientConnect;
        VirtualInvokeData OnClientDisconnect;
        VirtualInvokeData OnClientError;
        VirtualInvokeData OnClientNotReady;
        VirtualInvokeData OnClientChangeScene;
        VirtualInvokeData OnClientSceneChanged;
        VirtualInvokeData OnStartHost;
        VirtualInvokeData OnStartServer;
        VirtualInvokeData OnStartClient;
        VirtualInvokeData OnStopServer;
        VirtualInvokeData OnStopClient;
        VirtualInvokeData OnStopHost;
    };

    struct Mirror_NetworkManager_c
    {
        Il2CppClass_1 _1;
        struct Mirror_NetworkManager_StaticFields *static_fields;
        Il2CppRGCTXData *rgctx_data;
        Il2CppClass_2 _2;
        Mirror_NetworkManager_VTable vtable;
    };

    struct Mirror_NetworkManager_o
    {
        Mirror_NetworkManager_c *klass;
        void *monitor;
        Mirror_NetworkManager_Fields fields;
    };
}
