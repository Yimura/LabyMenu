#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/labyrinthine/Mirror/NetworkManager.hpp"

namespace YimMenu::Hooks
{
	void Labyrinthine::NetworkMgrSetupServer(Mirror_NetworkManager_o* this_, const MethodInfo* method)
	{
		this_->fields.maxConnections = 8;

		BaseHook::Get<NetworkMgrSetupServer, DetourHook<decltype(&NetworkMgrSetupServer)>>()->Original()(this_, method);
	}
}
