#pragma once
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include <cstdint>

namespace YimMenu
{
	class PlayerListUI_o; // forward decl

	// PlayerListUIItem - individual row in the game's player list UI
	// Field offsets verified via disassembly of SetPlayer, Init, SetPingSprite
	class PlayerListUIItem_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		TMP_Text* nameText;                    // 0x20
		struct UnityEngine_UI_Image_o* pingIcon; // 0x28
		struct UnityEngine_UI_Button_o* kickButton; // 0x30
		uint8_t playerIndex;                   // 0x38
		char _pad39[7];                        // alignment
		PlayerListUI_o* playerListUI;          // 0x40
	};
	static_assert(sizeof(PlayerListUIItem_o) == 0x48);
	static_assert(offsetof(PlayerListUIItem_o, playerIndex) == 0x38);
	static_assert(offsetof(PlayerListUIItem_o, playerListUI) == 0x40);

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct PlayerListUIItem_VTable
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

	struct PlayerListUIItem_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		PlayerListUIItem_VTable vtable;
	};
}
