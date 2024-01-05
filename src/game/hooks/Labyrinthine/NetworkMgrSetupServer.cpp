#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "game/labyrinthine/Mirror/NetworkManager.hpp"

namespace YimMenu::Hooks
{
    void Labyrinthine::NetworkMgrSetupServer(Mirror_NetworkManager_o* this_, const void* method)
    {
        this_->fields.maxConnections = 8;

        BaseHook::Get<Labyrinthine::NetworkMgrSetupServer, DetourHook<decltype(&NetworkMgrSetupServer)>>()->Original()(this_, method);
    }
}
