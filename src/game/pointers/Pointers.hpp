#pragma once
#include "game/labyrinthine/GameManager.hpp"
#include "game/labyrinthine/GfxDeviceDX11.hpp"
#include "game/labyrinthine/LobbyManager.hpp"
#include "game/labyrinthine/Mirror/NetworkRoomManager.hpp"
#include "game/labyrinthine/Monsters/AIManager.hpp"
#include "game/labyrinthine/PlayerListUI.hpp"
#include "game/labyrinthine/PlayerNetworkSync.hpp"
#include "game/labyrinthine/SimpleStaticWrapper.hpp"
#include "game/labyrinthine/UnityEngine/Vector3.hpp"

namespace YimMenu
{
	namespace Functions
	{
		using TMP_Text_getText = String* (*)(TMP_Text* this_, const void* method);
		using PlayerListUI_ServerKickPlayer = void (*)(PlayerListUI_o* this_, uint8_t playerIndex, const void* method);

		// Returns the Transform component on the same GameObject as the
		// passed Component. Internally calls an icall via cached fn-ptr.
		using Component_get_transform = void* (*)(void* component, const void* method);
		// Writes the world-space Vector3 position of the Transform into
		// outPos and returns outPos. Used to read live positions of
		// monsters/players without going through SyncVar slots that the
		// host never receives.
		using Transform_get_position = Vector3* (*)(Vector3* outPos, void* transform, const void* method);
	};

	struct PointerData
	{
		GfxDeviceDX11** GfxDeviceDX11;

		// functions
		SimpleStaticWrapper<NetworkRoomManager, 0x10> NetworkRoomManager;
		// Functions::TMP_Text_getText TMP_Text_getText;

		// hooks
		void* NetworkMgrSetupServer;

		// void* NetworkRoomMgrOnServerConnectInternal;
		// void* NetworkRoomMgrOnServerDisconnect;

		void* HasSupporterDlc;

		SimpleStaticWrapper<GameManager_o> GameManager;
		SimpleStaticWrapper<LobbyManager_o> LobbyMgr;
		SimpleStaticWrapper<PlayerListUI_o> PlayerListUI;
		SimpleStaticWrapper<AIManager_o> AIManager;
		SimpleStaticWrapper<PlayerNetworkSync_o> LocalPlayer;

		Functions::PlayerListUI_ServerKickPlayer ServerKickPlayer;

		Functions::Component_get_transform Component_get_transform;
		Functions::Transform_get_position  Transform_get_position;

		HWND Hwnd;
		WNDPROC OgWndProc;
		WNDPROC WndProc;
	};

	struct Pointers : PointerData
	{
		bool Init();
		void Restore();
	};

	inline YimMenu::Pointers Pointers;
}
