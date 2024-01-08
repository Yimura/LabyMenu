#pragma once
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "base/Array.hpp"

namespace YimMenu
{
	class PlayerListUI_Fields : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		Array<TMP_Text_o>* playerNameTexts;
		struct UnityEngine_UI_Image_array* playerPingIcons;
		float localPingUpdateInterval;
		float onlinePingUpdateInterval;
		Array<TMP_Text_o>* pingText;
		Array<TMP_Text_o>* livesText;
		Array<TMP_Text_o>* rndSeedText;
		struct ConnectionDebugger_o* connectionDebugger;
		struct UnityEngine_Sprite_array* pingIconsSet;
		struct UnityEngine_UI_Button_array* kickPlayerButtons;
		float localTimer;
		float onlineTimer;
		uint8_t localPlayerIndex;
	};

	struct PlayerListUI_o
	{
		void* klass;
		void* monitor;
		PlayerListUI_Fields fields;
	};
}
