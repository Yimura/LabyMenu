#include "Menu.hpp"

#include "core/renderer/Renderer.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	void Menu::Init()
	{
		Renderer::AddDXCallback(DrawMainMenu, -1);
	}

	void Menu::DrawMainMenu()
	{
		if (!GUI::IsOpen())
		{
			return;
		}

		if (ImGui::Begin("LabyMenu"))
		{
			if (ImGui::Button("Unload"))
			{
				g_Running = false;
			}

			ImGui::SeparatorText("Server Info:");
			if (const auto networkMgr = Pointers.GetNetworkMgrSingleTon(0, 0); networkMgr)
			{
				ImGui::Text("Max Connections: %d", networkMgr->fields.maxConnections);
			}
		}

		ImGui::End();
	}
}
