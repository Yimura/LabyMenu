#pragma once
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

namespace YimMenu
{
	class PlayerListUI_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		struct PlayerListUIItem_array* playerListItems;
		float localPingUpdateInterval;
		float onlinePingUpdateInterval;
		TMP_Text* pingText;
		TMP_Text* livesText;
		TMP_Text* rndSeedText;
		struct ConnectionDebugger_o* connectionDebugger;
		struct UnityEngine_Sprite_array* pingIconsSet;
		float localTimer;
		float onlineTimer;
		uint8_t localPlayerIndex;
	};
	static_assert(sizeof(PlayerListUI_o) == 0x68);
}
