#pragma once
#include "Death.hpp"
#include "Mirror/NetworkBehaviour.hpp"
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/LayerMask.hpp"
#include "UnityEngine/Nullable.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Vector3.hpp"
#include "base/String.hpp"

#include <cstdint>

namespace YimMenu
{
	class PlayerNetworkSync_Fields : public Mirror_NetworkBehaviour_Fields
	{
	public:
		int32_t _ID_k__BackingField;
		struct Flashlight_o* flashlight;
		struct System_Collections_Generic_List_Light__o* lanternLightsWithShadows;
		struct System_ValueTuple_HDAdditionalLightData__float__array* _AllLights_k__BackingField;
		bool networkReady;
		struct UnityEngine_GameObject_o* dissonanceVoice;
		String* playerName;
		uint64_t _steamID;
		LayerMask playerRaycastLayer;
		struct ValkoGames_Labyrinthine_Players_PlayerFootsteps_o* footsteps;
		struct ValkoGames_Labyrinthine_VR_Player_VRPlayer_o* _VRPlayer_k__BackingField;
		struct ValkoGames_Labyrinthine_Players_PlayerVFX_o* playerVFX;
		struct PlayerLook_o* playerLook;
		struct ValkoGames_Labyrinthine_Interactions_Drag_PlayerDragInteractionController_o* dragInteractionController;
		struct ValkoGames_Labyrinthine_Players_PlayerStunController_o* _StunController_k__BackingField;
		struct InventoryController_o* _InventoryController_k__BackingField;
		struct ValkoGames_Labyrinthine_Players_VFX_PlayerGhostOverlay_o* _PlayerGhostOverlay_k__BackingField;
		struct CharacterCustomization_CustomizationManager_o* _CustomizationManager_k__BackingField;
		struct UnityEngine_SkinnedMeshRenderer_array* VR_playerBodyRenderers;
		struct PlayerNetworkSync_BodyContainer_array* playerBodies;
		struct UnityEngine_Camera_o* cam;
		TMP_Text_o* namePlate;
		struct UnityEngine_Canvas_o* nameplateCanvas;
		struct UnityEngine_CanvasGroup_o* nameplateCanvasGroup;
		struct UnityEngine_AnimationCurve_o* nameplateAlphaOverDistance;
		struct UnityEngine_GameObject_o* audioGO;
		struct Dissonance_VoiceBroadcastTrigger_o* voiceBroadcastTrigger;
		struct AnimationHandler_o* animHandler;
		Death_o* death;
		int32_t _SafezoneType_k__BackingField;
		struct LightZone_o* _LastSafezone_k__BackingField;
		bool inWeather;
		struct UnityEngine_Coroutine_o* allPlayersDeadNoLivesLeftCoroutine;
		struct Vector3 position;
		Quaternion rotation;
		int8_t visualsRotation;
		uint8_t animationState;
		uint8_t leftArmState;
		uint8_t rightArmState;
		int16_t leftHandItemID;
		int16_t rightHandItemID;
		uint8_t verticalInput;
		bool isDead;
		bool _IsInKillSequence_k__BackingField;
		struct UnityEngine_GameObject_o* reviveCollider;
		struct PlayerLookData_o* playerLookData;
		struct ValkoGames_Labyrinthine_Cases_Inventory_RndPlayerInventory_o* rndPlayerInventory;
		struct UnityEngine_GameObject_o* glowstickObject;
		struct UnityEngine_Material_array* glowstickMaterials;
		struct UnityEngine_Material_array* supporterExtraGlowstickMaterials;
		uint8_t currentGlowstickMaterial;
		float syncPosRotInterval;
		float maxInterpolationTime;
		struct ValkoGames_Labyrinthine_Data_FloatSO_o* killSequenceEndMaxPositionDiff;
		struct ValkoGames_Labyrinthine_Data_FloatSO_o* killSequenceWaitingTimeout;
		float syncTimer;
		float _VerticalInputAngle_k__BackingField;
		struct Vector3 _Velocity_k__BackingField;
		Nullable<Vector3> _WaterLevelAtPlayerPos_k__BackingField;
		uint8_t _CurrentBody_k__BackingField;
		bool _IsCurrentBodyHeadless_k__BackingField;
		struct Vector3 lastPosition;
		struct Vector3 lastRemotePosition;
		struct Quaternion lastRemoteRotation;
		float lastRemoteVerticalInputAngle;
		float interpolationTimer;
		bool _spawnpointCheckForCheckpoint;
		struct ValkoGames_Labyrinthine_SpawnpointsManager_o* _spawnpointsManager;
		struct System_Action_o* MovedToSpawnpoint;
		struct System_Action_bool__o* OnDeathStatusChangeEvent;
		bool _canServerLoadLobby;
		struct Vector3 _LookDirection_k__BackingField;
		struct RaycastInfo_o* _PrevRaycast_k__BackingField;
		struct RaycastInfo_o* _LastRaycast_k__BackingField;
		RaycastHit lastExamineRaycast;
	};
	static_assert(sizeof(PlayerNetworkSync_Fields) == 0x280);

	class PlayerNetworkSync_o
	{
	private:
		void* klass;
		void* monitor;

	public:
		PlayerNetworkSync_Fields fields;
	};
}
