#pragma once
#include "base/String.hpp"

#include <cstdint>

namespace YimMenu
{
	// From il2cpp.h: ValkoGames_Labyrinthine_ClientData_Fields
	// Object layout: klass(0x00) + monitor(0x08) + fields(0x10)
	// Field offsets verified via disassembly of LobbyDummy$$OnClientDataSyncVarChanged
	struct ClientData_Fields
	{
		void* _ID_k__BackingField;                    // 0x00 - ValkoGames_Labyrinthine_NetworkID_o*
		String* _Name_k__BackingField;                // 0x08 - player display name
		uint8_t _NameplateColorIndex_k__BackingField; // 0x10
		bool _HasSupporterDLC_k__BackingField;        // 0x11
		char _pad12[6];                               // alignment
		void* _Avatar_k__BackingField;                // 0x18 - UnityEngine_Texture2D_o*
		uint8_t _ClientPlatform_k__BackingField;      // 0x20 - 0 = Steam
		bool _Demo_k__BackingField;                   // 0x21
	};

	class ClientData_o
	{
	public:
		void* klass;           // 0x00
		void* monitor;         // 0x08
		ClientData_Fields fields; // 0x10

		// Safely reads the player name from this ClientData.
		// rawPtr should be the clientData field from LobbyDummy/PlayerNetworkSync.
		// Returns empty string if data not yet synced (sentinel/null).
		static std::string GetPlayerName(void* rawPtr);
	};
	static_assert(offsetof(ClientData_o, fields) == 0x10);
	static_assert(offsetof(ClientData_Fields, _Name_k__BackingField) == 0x08);
}
