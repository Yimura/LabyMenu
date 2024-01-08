#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/labyrinthine/Mirror/NetworkManager.hpp"
#include "game/labyrinthine/Mirror/NetworkConnection.hpp"

namespace YimMenu::Hooks
{
	void Labyrinthine::NetworkManager_OnServerConnectInternal(Mirror_NetworkManager_o* this_, Mirror_NetworkConnection_o* conn, Mirror_ConnectMessage connectMsg, const MethodInfo* method)
	{
		BaseHook::Get<NetworkManager_OnServerConnectInternal, DetourHook<decltype(&NetworkManager_OnServerConnectInternal)>>()
		    ->Original()(this_, conn, connectMsg, method);
	}

	void Labyrinthine::NetworkManager_OnServerDisconnect(Mirror_NetworkManager_o* this_, Mirror_NetworkConnection_o* conn, const MethodInfo* method)
	{
		BaseHook::Get<NetworkManager_OnServerDisconnect, DetourHook<decltype(&NetworkManager_OnServerDisconnect)>>()->Original()(this_, conn, method);
	}
}
