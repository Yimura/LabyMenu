#pragma once
#include "TMPro/TMP_Text.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "base/String.hpp"

#include <cstdint>

namespace YimMenu
{
	class LobbyManager_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		struct UnityEngine_UI_Button_o* startGameButton;
		struct ValkoGames_Labyrinthine_UI_HelpUI_o* helpUI;
		struct UnityEngine_Transform_o* dummyCustomizationPosition;
		struct UnityEngine_GameObject_array* rerollTokens;
		struct ValkoGames_Labyrinthine_UI_HelpPopupWindow_o* _HelpPopupWindow_k__BackingField;
		struct ValkoGames_Labyrinthine_Scenes_Lobby_NoticeboardUIController_o* noticeboardUIController;
		struct UnityEngine_GameObject_o* donationPanel;
		float uiStateTransitionTime;
		int32_t cameraMoveTweenEase;
		int32_t cameraRotationTweenEase;
		struct LobbyManager_UIStateContainer_array* uiStates;
		struct LobbyManager_BackButtonOverride_array* backButtonOverrides;
		float lightTransitionTime;
		int32_t lightTransitionEase;
		struct ValkoGames_Labyrinthine_Systems_WorldSpaceUI_WSButton_array* buttonsToDisableInSettingsState;
		int32_t noticeboardStateIndex;
		int32_t customCasesStateIndex;
		float noiseScale;
		struct UnityEngine_Texture2D_o* dissolveNoise;
		struct System_Byte_array* dissolveNoiseBuffer;
		struct UnityEngine_Transform_o* vrPlayArea;
		int32_t currentUIState;
		struct DG_Tweening_Sequence_o* stateSequence;
		struct OptionsManager_o* optionsManager;
		struct UnityEngine_Camera_o* mainCamera;
		bool wasOptionsPanelActive;
		bool wasSelfModerationPanelActive;
		float initialCameraFov;
		bool canSwitchUIState;
		struct NetworkObjectReferences_o* networkObjectReferences;
		struct ValkoGames_Labyrinthine_Checkpoints_CheckpointUIController_o* _CheckpointUIController_k__BackingField;
		struct CharacterCustomization_LobbyFlashlightContainer_o* _FlashlightContainer_k__BackingField;
		struct ValkoGames_Labyrinthine_Store_StoreUIController_o* _StoreUIController_k__BackingField;
		struct System_Action_o* OnLobbyStartGame;
		struct UnityEngine_Animation_o* anim;
		struct UnityEngine_Transform_o* mainPlayerPos;
		struct UnityEngine_Transform_array* playerPositions;
		class LobbyDummy* mainDummy;
		struct System_Collections_Generic_List_LobbyDummy__o* players;
		struct System_Collections_Generic_Dictionary_int__LobbyDummy__o* serverAvailablePlayerPositions;
		TMP_Text* settingsText;
		bool settingsFocused;
		struct Localisation_LocalisedString_o* settingsFocusedTextLoc;
		struct ValkoGames_Labyrinthine_Systems_WorldSpaceUI_WSButton_o* infiniteLivesButton;
		struct UnityEngine_GameObject_o* infiniteLivesButtonDisabled;
		struct UnityEngine_GameObject_o* infiniteLivesButtonEnabled;
		TMP_Text* infiniteLivesText;
		float infiniteLivesDisabledAlpha;
		bool isServer;
		int32_t _SelectedStoryChapterNumber_k__BackingField;
		bool _AnyLevelSelected_k__BackingField;
		int32_t lockedChapters;
		struct Chapter_array* chapters;
		struct RandomGeneration_Contracts_ContractUI_array* customContracts;
		struct ValkoGames_Labyrinthine_Scenes_Lobby_LobbyStartGameButtonAnimations_o* lobbyStartGameButtonAnimations;
		bool canStartGame;
		String* settingsTextStr;
		struct UnityEngine_GameObject_o* lastSelectedUI;
	};
	static_assert(sizeof(LobbyManager_o) == 0x1B8);
}
