#include "Pointers.hpp"

#include "core/memory/BytePatch.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "core/renderer/Renderer.hpp"
#include "util/Joaat.hpp"

namespace YimMenu
{
	bool Pointers::Init()
	{
		const auto unity_player = ModuleMgr::Get("UnityPlayer.dll"_J);
		if (!unity_player)
		{
			LOG(FATAL) << "Could not find UnityPlayer.dll.";

			return false;
		}

		auto unity_scanner = PatternScanner(unity_player);

		constexpr auto gfxDeviceDX11 = Pattern<"44 8B ?? ?? 48 8B ?? ?? 4C 8B 35 ?? ?? ?? ?? 89 44 24 50">("GfxDeviceDX11");
		unity_scanner.Add(gfxDeviceDX11, [this](PointerCalculator ptr) {
			GfxDeviceDX11 = ptr.Add(11).Rip().As<class GfxDeviceDX11**>();
		});

		if (!unity_scanner.Scan())
		{
			LOG(FATAL) << "Failed to find GfxDeviceDX11 in UnityPlayer.dll";

			return false;
		}

		const auto main_module = ModuleMgr::Get("GameAssembly.dll"_J);
		if (!main_module)
		{
			LOG(FATAL) << "Could not find GameAssembly.dll.";

			return false;
		}

		auto scanner = PatternScanner(main_module);

		constexpr auto networkRoomMgrStaticInstance = Pattern<"48 8B 05 ?? ?? ?? ?? 48 89 5C 24 30 48 8B 88 B8 00 00 00 48 8B 49 10 48 85 C9">("NetworkManager::Static::Instance");
		scanner.Add(networkRoomMgrStaticInstance, [this](PointerCalculator ptr) {
			NetworkRoomManager = ptr.Add(3).Rip().As<void**>();
		});

		constexpr auto networkMgrSetupServer = Pattern<"40 88 78 49 48 8B 05 ?? ?? ?? ?? 48 8B 88 B8 00 00 00">("Mirror::NetworkManager::SetupServer");
		scanner.Add(networkMgrSetupServer, [this](PointerCalculator ptr) {
			NetworkMgrSetupServer = ptr.Sub(0x99).As<void*>();
		});

		// constexpr auto networkRoomMgrOnServerConnectInternal = Pattern<"48 8B F9 4C 8B 80 20 04 00 00">("Mirror::NetworkRoomMgr::OnServerConnectInternal");
		// scanner.Add(networkRoomMgrOnServerConnectInternal, [this](PointerCalculator ptr) {
		// 	NetworkRoomMgrOnServerConnectInternal = ptr.Sub(0xD7).As<void*>();
		// });

		// constexpr auto networkRoomMgrOnServerDisconnect = Pattern<"4C 8B 00 4D 85 C0 74 1D">("Mirror::NetworkRoomMgr::OnServerDisconnect");
		// scanner.Add(networkRoomMgrOnServerDisconnect, [this](PointerCalculator ptr) {
		// 	NetworkRoomMgrOnServerDisconnect = ptr.Sub(0xA0).As<void*>();
		// });

		// constexpr auto gameManagerStaticInstance = Pattern<"48 8B 05 ?? ?? ?? ?? 8B 9E 18 01 00 00">("GameManager::Static::Instance");
		// scanner.Add(gameManagerStaticInstance, [this](PointerCalculator ptr) {
		// 	GameManager = ptr.Add(3).Rip().As<void**>();
		// });

		constexpr auto lobbyMgrStaticInstance = Pattern<"48 8B 05 ?? ?? ?? ?? 48 89 5C 24 30 48 8B 90 B8 00 00 00 48 89 3A">("LobbyManager::Static::Instance");
		scanner.Add(lobbyMgrStaticInstance, [this](PointerCalculator ptr) {
			LobbyMgr = ptr.Add(3).Rip().As<void**>();
		});

		// constexpr auto playerListUi = Pattern<"48 8B 05 ?? ?? ?? ?? 48 8B D5 48 89 5C 24 30">("PlayerListUI::Static::Instance");
		// scanner.Add(playerListUi, [this](PointerCalculator ptr) {
		// 	PlayerListUI = ptr.Add(3).Rip().As<void**>();
		// });

		// constexpr auto tmpGetText = Pattern<"40 55 48 83 EC 20 80 B9">("TMP::Text::getText");
		// scanner.Add(tmpGetText, [this](PointerCalculator ptr) {
		// 	TMP_Text_getText = ptr.Add(3).Rip().As<Functions::TMP_Text_getText>();
		// });

		constexpr auto hasSupporterDlc = Pattern<"B9 00 35 25 00">("HasSupporterDlc");
		scanner.Add(hasSupporterDlc, [this](PointerCalculator ptr) {
			HasSupporterDlc = ptr.Sub(2).As<void*>();
		});

		if (!scanner.Scan())
		{
			LOG(FATAL) << "Some patterns could not be found, unloading.";

			return false;
		}

		if (Hwnd = FindWindowW(L"UnityWndClass", nullptr); !Hwnd)
		{
			LOG(FATAL) << "Failed to grab game window";

			return false;
		}

		return true;
	}

	void Pointers::Restore()
	{
	}
}
