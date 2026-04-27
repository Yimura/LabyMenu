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

		// PlayerNetworkSync$$OnStartClient: MOV [RAX+0x118],1 then loads GameManager_TypeInfo
		constexpr auto gameManagerStaticInstance = Pattern<"C7 80 18 01 00 00 01 00 00 00 48 8B 05 ?? ?? ?? ?? 48 8B 88 B8 00 00 00 48 8B 09">("GameManager::Static::Instance");
		scanner.Add(gameManagerStaticInstance, [this](PointerCalculator ptr) {
			GameManager = ptr.Add(13).Rip().As<void**>();
		});

		constexpr auto lobbyMgrStaticInstance = Pattern<"48 8B 05 ?? ?? ?? ?? 48 89 5C 24 30 48 8B 90 B8 00 00 00 48 89 3A">("LobbyManager::Static::Instance");
		scanner.Add(lobbyMgrStaticInstance, [this](PointerCalculator ptr) {
			LobbyMgr = ptr.Add(3).Rip().As<void**>();
		});

		constexpr auto playerListUi = Pattern<"48 8B 05 ?? ?? ?? ?? 48 8B D5 48 89 5C 24 30">("PlayerListUI::Static::Instance");
		scanner.Add(playerListUi, [this](PointerCalculator ptr) {
			PlayerListUI = ptr.Add(3).Rip().As<void**>();
		});

		// constexpr auto tmpGetText = Pattern<"40 55 48 83 EC 20 80 B9">("TMP::Text::getText");
		// scanner.Add(tmpGetText, [this](PointerCalculator ptr) {
		// 	TMP_Text_getText = ptr.Add(3).Rip().As<Functions::TMP_Text_getText>();
		// });

		// PlayerListUI$$ServerKickPlayer: unique CMP BL,[RDI+0x60] checking localPlayerIndex
		constexpr auto serverKickPlayer = Pattern<"80 78 39 00 74 ?? 3A 5F 60 74 ??">("PlayerListUI::ServerKickPlayer");
		scanner.Add(serverKickPlayer, [this](PointerCalculator ptr) {
			ServerKickPlayer = ptr.Sub(0x93).As<Functions::PlayerListUI_ServerKickPlayer>();
		});

		// AIManager$$GetAIControllers (parameterized): unique because it accesses
		// the aiControllers Dictionary at instance+0x40 (specific to AIManager).
		constexpr auto aiManagerStaticInstance = Pattern<"48 8B 05 ?? ?? ?? ?? 48 8B 88 B8 00 00 00 48 8B 01 48 85 C0 74 ?? 48 8B 48 40">("AIManager::Static::Instance");
		scanner.Add(aiManagerStaticInstance, [this](PointerCalculator ptr) {
			AIManager = ptr.Add(3).Rip().As<void**>();
		});

		// PlayerNetworkSync$$OnStartClient: reload of TypeInfo into RCX, +0xB8
		// deref, then write barrier, then read of __this->fields field at 0x108
		// (specific PNS field offset).
		constexpr auto playerNetworkSyncStaticInstance = Pattern<"48 8B 0D ?? ?? ?? ?? 48 8B 89 B8 00 00 00 E8 ?? ?? ?? ?? 48 8B 8F 08 01 00 00 48 85 C9">("PlayerNetworkSync::Static::Instance");
		scanner.Add(playerNetworkSyncStaticInstance, [this](PointerCalculator ptr) {
			LocalPlayer = ptr.Add(3).Rip().As<void**>();
		});

		// AIManager$$OnMonsterSpawned: a unique back-to-back call sequence to
		// Component.get_transform then Transform.get_position. Both helpers are
		// otherwise unpattern-scannable on their own (every Unity accessor
		// shares the same prologue+icall-cache shape). Resolves both function
		// addresses from this one anchor.
		constexpr auto componentTransformPositionCalls = Pattern<"48 85 DB 0F 84 ?? ?? ?? ?? 33 D2 48 8B CB E8 ?? ?? ?? ?? 48 85 C0 0F 84 ?? ?? ?? ?? 45 33 C0 48 8D 4C 24 38 48 8B D0 E8 ?? ?? ?? ??">("Component::get_transform + Transform::get_position");
		scanner.Add(componentTransformPositionCalls, [this](PointerCalculator ptr) {
			Component_get_transform = ptr.Add(15).Rip().As<Functions::Component_get_transform>();
			Transform_get_position  = ptr.Add(40).Rip().As<Functions::Transform_get_position>();
		});

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
