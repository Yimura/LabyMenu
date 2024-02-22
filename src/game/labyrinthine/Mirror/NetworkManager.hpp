#pragma once
#include "../UnityEngine/MonoBehaviour.hpp"
#include "../base/List.hpp"
#include "../base/String.hpp"
#include "../il2cpp/il2cpp.hpp"

#include <cstdint>

namespace YimMenu
{
	class Mirror_NetworkManager_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		bool dontDestroyOnLoad;
		bool runInBackground;
		bool autoStartServerBuild;
		bool showDebugMessages;
		int32_t serverTickRate;
		String* offlineScene;
		String* onlineScene;
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
		bool isNetworkActive;
		bool clientLoadedScene;
		int32_t _mode_k__BackingField;
		bool finishStartHostPending;
		uint8_t clientSceneOperation;
	};
	static_assert(sizeof(Mirror_NetworkManager_o) == 0x80);
}
