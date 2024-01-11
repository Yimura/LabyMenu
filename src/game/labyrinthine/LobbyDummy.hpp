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
		uint32_t maxPurchaseUnixTimeForMaleteen;
		TMP_Text* username;
		struct UnityEngine_GameObject_o* kickButton;
		struct UnityEngine_Transform_o* uiPoint;
		struct Michsky_UI_Dark_UIDissolveEffect_o* playerUIDissolve;
		struct UnityEngine_RectTransform_o* playerUIRect;
		TMP_Text* levelText;
		struct UnityEngine_UI_RawImage_o* playerAvatar;
		struct UnityEngine_UI_Image_o* playerFrame;
		Color playerFrameColorDLC;
		int32_t currentBodyIndex;
		struct UnityEngine_GameObject_o* characterSelectionButtons;
		struct LobbyDummy_BodyTypeWithGameObject_array* bodies;
		struct Dissonance_VoiceBroadcastTrigger_o* voiceBroadcastTrigger;
		uint8_t body;
		uint64_t m_SteamID;
		int32_t Experience;
		bool hasDlc;
		struct UnityEngine_Canvas_o* playerUICanvas;
		Vector3 canvasScaleVR;
		struct UnityEngine_Camera_o* mainCamera;
		float customizationBodyRotation;
		float controllerRotationSpeed;
		float lastMousePositionX;
		float startEulerY;
		int32_t SpawnpointIndex;
		Vector3 targetPosition;
		struct System_Action_PlayerBody__o* OnBodyChanged;
		bool canChangeBody;
		bool inCustomizationUI;
		struct UnityEngine_Coroutine_o* steamAvatarCoroutine;
	};
	static_assert(sizeof(LobbyDummy) == 0x130);
}
