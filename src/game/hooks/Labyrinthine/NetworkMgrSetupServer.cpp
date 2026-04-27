#include "core/hooking/DetourHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/labyrinthine/Mirror/NetworkManager.hpp"

namespace YimMenu::Hooks
{
	void Labyrinthine::NetworkMgrSetupServer(Mirror_NetworkManager_o* this_, const MethodInfo* method)
	{
		this_->maxConnections = 16;

		// Demo: dispatch a virtual call through the typed vtable. The signature
		// (`System_String_o*()`) lives in Mirror_NetworkManager_VTable::ToString
		// (slot _3_ToString in the dump); the call site only supplies `this_`.
		// The trailing MethodInfo* is appended by VTableSlot::operator()
		// automatically. Unity's MonoBehaviour.ToString returns
		// "GameObjectName (TypeName)" — useful for telling concrete subclasses
		// (e.g. ValkoNetworkManager) apart.
		auto* nameStr = Klass<Mirror_NetworkManager_c>(this_)->vtable.ToString(this_);
		LOG(INFO) << "Server starting on: " << reinterpret_cast<String*>(nameStr)->str();

		BaseHook::Get<NetworkMgrSetupServer, DetourHook<decltype(&NetworkMgrSetupServer)>>()->Original()(this_, method);
	}
}
