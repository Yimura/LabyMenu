#pragma once
#include "Mirror/NetworkBehaviour.hpp"
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Vector3.hpp"

#include <cstdint>

namespace YimMenu
{
	class LobbyDummy : public Mirror_NetworkBehaviour_Fields
	{
	public:
		// Mirrors PlayerSave::GetLevel — converts raw XP to level.
		// Each level N costs (N + 5) * 10 XP.
		static uint16_t GetLevel(int32_t experience)
		{
			uint16_t level = 1;
			while (level < 9999)
			{
				experience -= (level + 5) * 10;
				if (experience < 1)
					break;
				level++;
			}
			return level;
		}

		uint32_t maxPurchaseUnixTimeForMaleteen;
		TMP_Text* username;
		TMP_Text* platformIndicator;
		struct UnityEngine_GameObject_o* kickButton;
		struct UnityEngine_Transform_o* uiPoint;
		struct UnityEngine_Transform_o* uiPointSecond;
		struct Michsky_UI_Dark_UIDissolveEffect_o* playerUIDissolve;
		struct UnityEngine_RectTransform_o* playerUIRect;
		TMP_Text* levelText;
		struct UnityEngine_UI_RawImage_o* playerAvatar;
		struct UnityEngine_UI_Image_o* playerFrame;
		struct UnityEngine_Color_array* playerFrameColors;
		struct UnityEngine_Texture2D_o* fallbackAvatarTexture;
		struct System_String_o* animationPropertyName;
		struct LobbyDummy_SpecialAnimation_array* animations;
		int32_t randomAnimationDelayMin;
		int32_t randomAimationDelayMax;
		int32_t currentBodyIndex;
		struct ValkoGames_Labyrinthine_Misc_Timer_o* randomAnimationTimer;
		struct UnityEngine_GameObject_o* characterSelectionButtons;
		struct LobbyDummy_BodyTypeWithGameObject_array* bodies;
		struct Dissonance_VoiceBroadcastTrigger_o* voiceBroadcastTrigger;
		uint8_t body;
		bool _WasPlayerBodySet_k__BackingField;
		struct ValkoGames_Labyrinthine_ClientData_o* clientData;
		int32_t Experience;
		struct UnityEngine_Canvas_o* playerUICanvas;
		Vector3 canvasScaleVR;
		struct UnityEngine_Camera_o* mainCamera;
		float customizationBodyRotation;
		float controllerRotationSpeed;
		float lastMousePositionX;
		float startEulerY;
		int32_t SpawnpointIndex;
		bool isOwnedByServer;
		Vector3 targetPosition;
		struct System_Action_PlayerBody__o* OnBodyChanged;
		bool canChangeBody;
		bool inCustomizationUI;
		struct System_Action_byte__byte__o* _Mirror_SyncVarHookDelegate_body;
		struct System_Action_ClientData__ClientData__o* _Mirror_SyncVarHookDelegate_clientData;
		struct System_Action_int__int__o* _Mirror_SyncVarHookDelegate_Experience;
		struct System_Action_int__int__o* _Mirror_SyncVarHookDelegate_SpawnpointIndex;
	};
	static_assert(sizeof(LobbyDummy) == 0x1A0);
}
