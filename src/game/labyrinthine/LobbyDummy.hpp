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

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct LobbyDummy_VTable
	{
		// _0_Equals
		VTableSlot<bool(Il2CppObject*)>                                Equals;
		// _1_Finalize
		VTableSlot<void()>                                             Finalize;
		// _2_GetHashCode
		VTableSlot<int32_t()>                                          GetHashCode;
		// _3_ToString
		VTableSlot<System_String_o*()>                                 ToString;
		// _4_OnValidate
		VTableSlot<void()>                                             OnValidate;
		// _5_OnSerialize
		VTableSlot<bool(Mirror_NetworkWriter_o*, bool)>                OnSerialize;
		// _6_OnDeserialize
		VTableSlot<void(Mirror_NetworkReader_o*, bool)>                OnDeserialize;
		// _7_SerializeSyncVars
		VTableSlot<bool(Mirror_NetworkWriter_o*, bool)>                SerializeSyncVars;
		// _8_DeserializeSyncVars
		VTableSlot<void(Mirror_NetworkReader_o*, bool)>                DeserializeSyncVars;
		// _9_OnStartServer
		VTableSlot<void()>                                             OnStartServer;
		// _10_OnStopServer
		VTableSlot<void()>                                             OnStopServer;
		// _11_OnStartClient
		VTableSlot<void()>                                             OnStartClient;
		// _12_OnStopClient
		VTableSlot<void()>                                             OnStopClient;
		// _13_OnStartLocalPlayer
		VTableSlot<void()>                                             OnStartLocalPlayer;
		// _14_OnStopLocalPlayer
		VTableSlot<void()>                                             OnStopLocalPlayer;
		// _15_OnStartAuthority
		VTableSlot<void()>                                             OnStartAuthority;
		// _16_OnStopAuthority
		VTableSlot<void()>                                             OnStopAuthority;
		// _17_Weaved
		VTableSlot<void()>                                             Weaved;
	};

	struct LobbyDummy_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		LobbyDummy_VTable vtable;
	};
}
