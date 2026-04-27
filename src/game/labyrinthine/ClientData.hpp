#pragma once
#include "base/String.hpp"
#include "il2cpp/il2cpp.hpp"

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

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct ClientData_VTable
	{
		// _0_Equals
		VTableSlot<bool(Il2CppObject*)>     Equals;
		// _1_Finalize
		VTableSlot<void()>                  Finalize;
		// _2_GetHashCode
		VTableSlot<int32_t()>               GetHashCode;
		// _3_ToString
		VTableSlot<System_String_o*()>      ToString;
	};

	struct ClientData_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		ClientData_VTable vtable;
	};
}
