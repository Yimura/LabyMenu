#pragma once
#include "ConnectionDebugger.hpp"
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include <cstdint>

namespace YimMenu
{
	class PlayerListUI_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		struct PlayerListUIItem_array* playerListItems; // 0x20
		float localPingUpdateInterval;              // 0x28
		float onlinePingUpdateInterval;             // 0x2c
		TMP_Text* pingText;                         // 0x30
		TMP_Text* livesText;                        // 0x38
		TMP_Text* rndSeedText;                      // 0x40
		ConnectionDebugger_o* connectionDebugger;   // 0x48
		struct UnityEngine_Sprite_array* pingIconsSet; // 0x50
		float localTimer;                           // 0x58
		float onlineTimer;                          // 0x5c
		uint8_t localPlayerIndex;                   // 0x60
	};
	static_assert(sizeof(PlayerListUI_o) == 0x68);
}
