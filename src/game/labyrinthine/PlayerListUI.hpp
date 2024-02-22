#pragma once
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "base/Array.hpp"

namespace YimMenu
{
	class PlayerListUI_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		Array<TMP_Text>* playerNameTexts;
		struct UnityEngine_UI_Image_array* playerPingIcons;
		float localPingUpdateInterval;
		float onlinePingUpdateInterval;
		Array<TMP_Text>* pingText;
		Array<TMP_Text>* livesText;
		Array<TMP_Text>* rndSeedText;
		struct ConnectionDebugger_o* connectionDebugger;
		struct UnityEngine_Sprite_array* pingIconsSet;
		struct UnityEngine_UI_Button_array* kickPlayerButtons;
		float localTimer;
		float onlineTimer;
		uint8_t localPlayerIndex;
	};
	static_assert(sizeof(PlayerListUI_o) == 0x70);
}
