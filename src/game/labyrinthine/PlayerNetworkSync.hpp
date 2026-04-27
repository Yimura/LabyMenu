#pragma once
#include "Death.hpp"
#include "Mirror/NetworkBehaviour.hpp"
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/LayerMask.hpp"
#include "UnityEngine/Nullable.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Vector3.hpp"
#include <cstdint>

namespace YimMenu
{

	class PlayerNetworkSync_o : public Mirror_NetworkBehaviour_Fields
	{
	public:
		int32_t _ID_k__BackingField;
		struct Flashlight_o* flashlight;
		struct System_Collections_Generic_List_Light__o* lanternLightsWithShadows;
		struct System_ValueTuple_HDAdditionalLightData__float__array* _AllLights_k__BackingField;
		bool networkReady;
		struct ValkoGames_Labyrinthine_ClientData_o* _ClientData_k__BackingField;
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
		TMP_Text* namePlate;
		struct UnityEngine_Canvas_o* nameplateCanvas;
		struct UnityEngine_CanvasGroup_o* nameplateCanvasGroup;
		struct UnityEngine_AnimationCurve_o* nameplateAlphaOverDistance;
		struct UnityEngine_GameObject_o* audioGO;
		struct Dissonance_VoiceBroadcastTrigger_o* voiceBroadcastTrigger;
		struct AnimationHandler_o* animHandler;
		Death* death;
		int32_t _SafezoneType_k__BackingField;
		struct LightZone_o* _LastSafezone_k__BackingField;
		bool inWeather;
		bool _AnyDataReceived_k__BackingField;
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
		bool _WasPlayerBodySet_k__BackingField;
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
		struct System_Action_bool__bool__o* _Mirror_SyncVarHookDelegate_isDead;
	};
	static_assert(sizeof(PlayerNetworkSync_o) == 0x2A8);

	// Same vtable shape as Mirror_NetworkBehaviour (no PlayerNetworkSync-specific
	// virtuals in the dump). Calls dispatch to PlayerNetworkSync's overrides at
	// runtime via the per-instance klass.
	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct PlayerNetworkSync_VTable
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

	struct PlayerNetworkSync_StaticFields
	{
		PlayerNetworkSync_o* instance;
	};

	struct PlayerNetworkSync_c
	{
		Il2CppClass_1 _1;
		PlayerNetworkSync_StaticFields* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		PlayerNetworkSync_VTable vtable;
	};
}
