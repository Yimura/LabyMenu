#pragma once
#include "game/labyrinthine/Mirror/NetworkManager.hpp"

namespace YimMenu
{
	namespace Functions
	{
		using GetNetworkMgrSingleton = Mirror_NetworkManager_o*(*)(int64_t a1, bool LastSave);
	};

	struct PointerData
	{
		std::array<void*, 18> SwapchainVtable;

		// functions
		Functions::GetNetworkMgrSingleton GetNetworkMgrSingleTon;

		// hooks
		void* NetworkMgrSetupServer;

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
