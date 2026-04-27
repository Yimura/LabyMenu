#pragma once

namespace YimMenu::MonsterAwareness
{
	struct Settings
	{
		bool  enabled      = false;
		float maxDistanceM = 50.0f; // [5, 200]
	};

	// Called once during init alongside Menu::Init(). Registers the always-on
	// overlay DX callback (independent of whether the menu is open).
	void Init();

	// Returns the live settings struct so the menu UI can edit it directly.
	Settings& GetSettings();

	// Renders the settings widgets (checkbox + slider) inside the existing
	// menu's tab bar. Call from Menu::DrawMainMenu().
	void DrawSettingsTab();
}
