#pragma once
#include "Mirror/NetworkBehaviour.hpp"
#include "UnityEngine/LayerMask.hpp"
#include "UnityEngine/Vector3.hpp"

#include <cstdint>

namespace YimMenu
{
	class Death : public Mirror_NetworkBehaviour_Fields
	{
	public:
        struct ValkoGames_Labyrinthine_Cases_Inventory_RndInventoryItemSO_o* selfReviveItem;
        struct UnityEngine_CharacterController_o* _ccontroller;
        struct PlayerControl_o* playerControl;
        struct PlayerLook_o* playerLook;
        struct PlayerNetworkSync_o* playerNetworkSync;
        struct PlayerAnimator_o* playerAnimator;
        struct UnityEngine_GameObject_o* killLight;
        float spawnProtectionDuration;
        float stantingUpAnimDuration;
        LayerMask playerLayerMask;
        float raycastRevivalMaxDistance;
        struct UnityEngine_Canvas_o* veinsCanvas;
        struct UnityEngine_UI_Image_o* veinsImage;
        float bleedoutTimeout;
        float revivalTime;
        Vector3 bleedoutLocalCameraPosition;
        Vector3 localCameraPositionWhenSpectating;
        struct UnityEngine_GameObject_o* spectateCameraRoot;
        struct UnityEngine_Transform_o* spectateCamera;
        int32_t spectateIndex;
        struct UnityEngine_Transform_o* headToSpectateFollow;
        struct UnityEngine_AudioSource_o* deathMusic;
        struct UnityEngine_AudioSource_o* killAudioSource;
        struct UnityEngine_AudioClip_array* killClips;
        bool isSelfReviveAvailable;
        struct System_Action_o* SpectateModeStarted;
        struct ValkoGames_Labyrinthine_Players_Death_PlayerRespawnEventHandler_o* Respawned;
        struct DG_Tweening_Tween_o* bleedoutTween;
        struct DG_Tweening_Sequence_o* veinsTween;
        struct DG_Tweening_Tween_o* revivalTween;
        struct DG_Tweening_TweenCallback_o* enableIKAction;
        struct PlayerNetworkSync_o* _SpectateTarget_k__BackingField;
        int32_t lastKillerMonster;
        struct ValkoGames_Labyrinthine_Players_Death_Inputs_o* inputs;
        bool waitForLeftMouseButtonRelease;
        bool waitForRightMouseButtonRelease;
        float giveUpTime;
        float selfReviveTime;
        struct UIMessagesController_VRInputMessage_o* vrGiveupInputMessage;
        struct UIMessagesController_VRInputMessage_o* vrSelfreiveInputMessage;
        struct Death* revivalTarget;
        bool _IsRespawning_k__BackingField;
        bool isBeingRevived;
        double reviveStartTime;
        double bleedoutStartTime;
        float giveUpTimer;
        float selfReviveTimer;
        float reviveCooldown;
        float reviveMsgCooldown;
        struct System_Action_bool__bool__o* _Mirror_SyncVarHookDelegate_isSelfReviveAvailable;
    };
    static_assert(sizeof(Death) == 0x1C0);

	// Slots 0-17 are NetworkBehaviour-inherited; 18-23 are Death-specific.
	// Specific slot signatures (SetupSpectateMode/StartSpectateMode/etc.) default
	// to void() — refine when invoking.
	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct Death_VTable
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
		// _18_SetupSpectateMode
		VTableSlot<void()>                                             SetupSpectateMode;
		// _19_StartSpectateMode
		VTableSlot<void()>                                             StartSpectateMode;
		// _20_OnSpectateModeStarted
		VTableSlot<void()>                                             OnSpectateModeStarted;
		// _21_UpdateInputs
		VTableSlot<void()>                                             UpdateInputs;
		// _22_TryGetPlayerToRevive
		VTableSlot<void()>                                             TryGetPlayerToRevive;
		// _23_RevivalTweenOnUpdate
		VTableSlot<void()>                                             RevivalTweenOnUpdate;
	};

	struct Death_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		Death_VTable vtable;
	};
}
