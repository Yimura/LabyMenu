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
			
			ImGui::SeparatorText("GameMgr Info:");
			if (const auto gameMgr = Pointers.GameManager.Get(); gameMgr)
			{
				ImGui::Text("Player List:");
				if (const auto players = gameMgr->fields.playersOrdered; players)
				{
					for (const auto& player : *gameMgr->fields.playersOrdered)
					{
						if (player.fields.networkReady)
						{
							ImGui::Text("%s", player.fields.playerName->s().c_str());
						}
					}
				}
			}
			else ImGui::Text("No active GameManager found.");

			if (const auto networkMgr = Pointers.GetNetworkMgrSingleTon(0, 0); networkMgr)
			{
				ImGui::SeparatorText("Server Info:");
				if (!networkMgr->fields.finishStartHostPending && networkMgr->fields.isNetworkActive)
				{
				}

				ImGui::Text("Max Connections: %d", networkMgr->fields.maxConnections);
			}
			else ImGui::Text("No active NetworkManager found.");
		}

		ImGui::End();
	}
}
