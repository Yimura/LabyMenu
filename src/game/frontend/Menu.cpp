#include "Menu.hpp"

#include "core/renderer/Renderer.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu
{
	void Menu::Init()
	{
		Renderer::AddDXCallback(DrawMainMenu, -1);
	}

	void Main()
	{
		if (ImGui::BeginTabItem("Main"))
		{
			ImGui::SeparatorText("LobbyMgr Info:");
			const auto lobbyMgr = Pointers.LobbyMgr.Get();
			const auto networkMgr = Pointers.GetNetworkMgrSingleTon(0, 0);
			if (lobbyMgr && networkMgr && !networkMgr->finishStartHostPending && networkMgr->isNetworkActive)
			{
				ImGui::Text("Lobby Info:");
				if (lobbyMgr->mainDummy)
				{
					ImGui::Text("Player: %s", lobbyMgr->mainDummy->username->m_text->s().c_str());
				}
				auto players = lobbyMgr->serverAvailablePlayerPositions->Values();
				for (size_t i = 0; i < players.Count(); ++i)
				{
					const auto player = players[i];
					ImGui::Text("Player: %s", player.username->m_text->s().c_str());
				}

				ImGui::Text("Max Connections: %d", networkMgr->maxConnections);
			}
			else ImGui::Text("No active LobbyManager found.");

			ImGui::EndTabItem();
		}
	}

	void Debug()
	{
		if (ImGui::BeginTabItem("Debug"))
		{
			ImGui::SeparatorText("GameMgr Info:");
			if (const auto gameMgr = Pointers.GameManager.Get(); gameMgr)
			{
				ImGui::Text("Player List:");
				if (const auto players = gameMgr->playersOrdered; players)
				{
					for (const auto& player : *gameMgr->playersOrdered)
					{
						if (player.networkReady)
						{
							ImGui::Text("%s", player.playerName->s().c_str());
						}
					}
				}
			}
			else ImGui::Text("No active GameManager found.");

			ImGui::SeparatorText("PlayerListUI:");
			if (const auto playerListUi = Pointers.PlayerListUI.Get(); playerListUi)
			{
				for (auto player : *playerListUi->playerNameTexts)
				{
					ImGui::Text("Player: %s", player.m_text->s().c_str());
				}
			}
			else ImGui::Text("No active PlayerListUI found.");

			ImGui::SeparatorText("NetworkRoomManager Info:");
			if (const auto networkRoomMgr = Pointers.GetNetworkMgrSingleTon(0, 1); networkRoomMgr)
			{
				for (auto player : *networkRoomMgr->roomSlots)
				{
					ImGui::Text("PlayerID: %d", player.index);
				}
			}
			else ImGui::Text("No active NetworkRoomManager found.");

			ImGui::EndTabItem();
		}
	}

	void Menu::DrawMainMenu()
	{
		if (!GUI::IsOpen())
		{
			return;
		}

		if (ImGui::Begin("LabyMenu"))
		{
			ImGui::BeginTabBar("Main");
			Main();
			Debug();
			ImGui::EndTabBar();

			ImGui::Separator();
			if (ImGui::Button("Unload"))
			{
				g_Running = false;
			}
		}

		ImGui::End();
	}
}
