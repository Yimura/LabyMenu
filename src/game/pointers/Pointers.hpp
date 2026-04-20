#pragma once
#include "game/labyrinthine/GameManager.hpp"
#include "game/labyrinthine/GfxDeviceDX11.hpp"
#include "game/labyrinthine/LobbyManager.hpp"
#include "game/labyrinthine/Mirror/NetworkRoomManager.hpp"
#include "game/labyrinthine/PlayerListUI.hpp"
#include "game/labyrinthine/SimpleStaticWrapper.hpp"

namespace YimMenu
{
	namespace Functions
	{
		using TMP_Text_getText = String* (*)(TMP_Text* this_, const void* method);
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

		// SimpleStaticWrapper<GameManager_o> GameManager;
		SimpleStaticWrapper<LobbyManager_o> LobbyMgr;
		// SimpleStaticWrapper<PlayerListUI_o> PlayerListUI;

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
