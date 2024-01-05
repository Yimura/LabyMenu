#include "common.hpp"
#include "core/filemgr/FileMgr.hpp"
#include "core/hooking/Hooking.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/frontend/GUI.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	DWORD Main(void*)
	{
		const auto documents = std::filesystem::path(std::getenv("USERPROFILE")) / "Documents";
		FileMgr::Init(documents / "LabyMenu");

		LogHelper::Init("LabyMenu", FileMgr::GetProjectFile("./cout.log"));

		// Settings::Initialize(FileMgr::GetProjectFile("./settings.json"));

		if (!ModuleMgr::RefreshModuleList())
			goto unload;
		if (!Pointers.Init())
			goto unload;

		Hooking::Init();
		GUI::Init();

		while (g_Running)
		{
			// Needed incase UI is malfunctioning or for emergencies
			if (GetAsyncKeyState(VK_DELETE) & 0x8000)
			{
				g_Running = false;
			}

			std::this_thread::sleep_for(100ms);
			// Settings::Save(); // TODO: move this somewhere else
		}

		LOG(INFO) << "Unloading";

	unload:
		Hooking::Destroy();
		Renderer::Destroy();
		Pointers.Restore();

		LogHelper::Destroy();

		CloseHandle(g_MainThread);
		FreeLibraryAndExitThread(g_DllInstance, EXIT_SUCCESS);

		return EXIT_SUCCESS;
	}
}

BOOL WINAPI DllMain(HINSTANCE dllInstance, DWORD reason, void*)
{
	using namespace YimMenu;

	DisableThreadLibraryCalls(dllInstance);

	if (reason == DLL_PROCESS_ATTACH)
	{
		g_DllInstance = dllInstance;

		g_MainThread = CreateThread(nullptr, 0, Main, nullptr, 0, &g_MainThreadId);
	}
	return true;
}
