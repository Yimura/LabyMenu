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
    };
    static_assert(sizeof(Death) == 0x198);
}
