#include "Menu.hpp"

#include "core/renderer/Renderer.hpp"
#include "game/features/MonsterAwareness/MonsterAwareness.hpp"
#include "game/labyrinthine/ClientData.hpp"
#include "game/labyrinthine/LobbyDummy.hpp"
#include "game/labyrinthine/PlayerListUI.hpp"
#include "game/labyrinthine/PlayerListUIItem.hpp"
#include "game/labyrinthine/base/List.hpp"
#include "game/pointers/Pointers.hpp"
#include "imgui.h"

#include <format>

namespace YimMenu
{
	void Menu::Init()
	{
		Renderer::AddDXCallback(DrawMainMenu, -1);
	}

	static void DrawLobbyPlayers()
	{
		const auto lobbyMgr = Pointers.LobbyMgr.Get();
		if (!lobbyMgr || !lobbyMgr->players)
			return;

		auto* players = reinterpret_cast<List<LobbyDummy*>*>(lobbyMgr->players);
		const auto lobbyPlayerCount = std::format("Lobby Players ({})", players->size());
		ImGui::SeparatorText(lobbyPlayerCount.c_str());

		if (auto* local = lobbyMgr->mainDummy;
		    local && local->username && local->username->m_text && !local->username->m_text->IsEmpty())
		{
			auto name = local->username->m_text->str();
			ImGui::Text("[You] %s (Lvl: %d)", name.c_str(), LobbyDummy::GetLevel(local->Experience));
		}

		for (auto* dummy : *players)
		{
			if (!dummy || dummy == lobbyMgr->mainDummy)
				continue;
			if (!dummy->username || !dummy->username->m_text || dummy->username->m_text->IsEmpty())
				continue;

			auto name = dummy->username->m_text->str();
			ImGui::Text("%s (Lvl: %d)", name.c_str(), LobbyDummy::GetLevel(dummy->Experience));
		}
	}

	static void DrawInGamePlayers()
	{
		const auto playerListUI = Pointers.PlayerListUI.Get();
		const auto gameMgr      = Pointers.GameManager.Get();

		if (!playerListUI || !gameMgr || !gameMgr->players)
		{
			ImGui::Separator();
			ImGui::Text("No active GameManager found.");
			return;
		}

		int localPing = -1;
		if (auto* cd = playerListUI->connectionDebugger)
			localPing = cd->_Ping_k__BackingField;

		const auto header = std::format("In-Game Players ({}) - Ping: {}ms", gameMgr->players->size(), localPing >= 0 ? std::to_string(localPing) : "?");
		ImGui::SeparatorText(header.c_str());

		for (auto* player : *gameMgr->players)
		{
			if (!player || !player->networkReady)
				continue;

			auto name = ClientData_o::GetPlayerName(player->_ClientData_k__BackingField);
			if (name.empty())
				continue;

			bool isLocal = (player->_ID_k__BackingField == static_cast<int32_t>(playerListUI->localPlayerIndex));

			ImGui::PushID(player->_ID_k__BackingField);

			if (isLocal)
				ImGui::Text("[%d] %s (You) %s", player->_ID_k__BackingField, name.c_str(), player->isDead ? "(Dead)" : "");
			else
				ImGui::Text("[%d] %s %s", player->_ID_k__BackingField, name.c_str(), player->isDead ? "(Dead)" : "");

			if (!isLocal && Pointers.ServerKickPlayer)
			{
				ImGui::SameLine();
				auto kickLabel = std::format("Kick##{}", player->_ID_k__BackingField);
				if (ImGui::Button(kickLabel.c_str()))
				{
					Pointers.ServerKickPlayer(playerListUI, static_cast<uint8_t>(player->_ID_k__BackingField), nullptr);
				}
			}

			ImGui::PopID();
		}
	}

	static void DrawMainTab()
	{
		if (ImGui::BeginTabItem("Main"))
		{
			ImGui::SeparatorText("LobbyMgr Info:");
			const auto networkMgr = Pointers.NetworkRoomManager.Get();

			if (!networkMgr || networkMgr->finishStartHostPending || networkMgr->_mode_k__BackingField == 0)
			{
				ImGui::Text("Not connected.");
				ImGui::EndTabItem();
				return;
			}

			ImGui::Text("Max Connections: %d", networkMgr->maxConnections);
			DrawLobbyPlayers();
			DrawInGamePlayers();
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
			DrawMainTab();
			MonsterAwareness::DrawSettingsTab();
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
