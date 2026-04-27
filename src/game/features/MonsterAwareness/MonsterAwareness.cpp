#include "MonsterAwareness.hpp"

#include "core/renderer/Renderer.hpp"
#include "game/labyrinthine/Monsters/AIController.hpp"
#include "game/labyrinthine/Monsters/AIManager.hpp"
#include "game/labyrinthine/Monsters/MonsterNetworkSync.hpp"
#include "game/labyrinthine/PlayerNetworkSync.hpp"
#include "game/labyrinthine/base/List.hpp"
#include "game/pointers/Pointers.hpp"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <imgui.h>
#include <string>
#include <string_view>
#include <vector>

namespace YimMenu::MonsterAwareness
{
	namespace
	{
		Settings s_Settings{};

		struct MonsterInfo
		{
			std::string name;     // class name with "NetworkSync" stripped
			float       distance; // metres from local player
			bool        chasing;
		};

		// Validates that a pointer falls in the user-space heap range used by
		// IL2CPP managed objects. Catches both null and the various sentinel
		// values described in the unity-reversing reference.
		inline bool IsValidPtr(const void* p)
		{
			const auto v = reinterpret_cast<std::uintptr_t>(p);
			return v > 0x10000 && v < 0x7FFFFFFFFFFFull;
		}

		// Reads the C# class name from the Il2CppClass metadata. The pointer
		// chain (klass → Il2CppClass_1.name → const char*) is set up by the
		// IL2CPP runtime and stable for any spawned managed object.
		std::string DisplayName(const MonsterNetworkSync_o* sync)
		{
			if (!IsValidPtr(sync))
				return "?";

			const auto* klass = *reinterpret_cast<const Il2CppClass* const*>(sync);
			if (!IsValidPtr(klass))
				return "?";

			const char* raw = klass->_1.name;
			if (!IsValidPtr(raw))
				return "?";

			std::string name(raw);
			// Strip the trailing "NetworkSync" so labels read "Bat" instead of
			// "BatNetworkSync". Falls back to the full name for any types that
			// don't follow this convention.
			constexpr std::string_view suffix = "NetworkSync";
			if (name.size() > suffix.size() &&
			    name.compare(name.size() - suffix.size(), suffix.size(), suffix) == 0)
			{
				name.erase(name.size() - suffix.size());
			}
			return name;
		}

		// IL2CPP List<T*> raw layout (bypassing the project's List/Array iterator,
		// which mistypes elements by one indirection level for T=pointer):
		//   List<T*>:  klass(8) + monitor(8) + _items*(8) + _size(4) + _version(4)
		//              + _syncRoot(8)  → element-pointer slots at offsets 0x10/0x18.
		//   Array<T*>: klass(8) + monitor(8) + bounds*(8) + max_length(8)
		//              + T* items[max_length] starting at offset 0x20.
		template<typename T>
		struct RawListView
		{
			T* const* items; // pointer to first element of the inline array
			int32_t   size;  // logical element count
		};

		template<typename T>
		RawListView<T> ViewList(const void* listObj)
		{
			RawListView<T> v{nullptr, 0};
			if (!IsValidPtr(listObj))
				return v;
			const auto* base    = reinterpret_cast<const char*>(listObj);
			const auto* arr     = *reinterpret_cast<const char* const*>(base + 0x10); // _items
			const int32_t lsize = *reinterpret_cast<const int32_t*>(base + 0x18);     // _size
			if (!IsValidPtr(arr) || lsize <= 0)
				return v;
			const int32_t maxLen = static_cast<int32_t>(
			    *reinterpret_cast<const std::uintptr_t*>(arr + 0x18));   // max_length
			v.items = reinterpret_cast<T* const*>(arr + 0x20);            // inline items[]
			v.size  = std::min(lsize, maxLen);
			return v;
		}

		// Reads the live world-space position of any Component (MonoBehaviour-
		// derived) by chaining the cached Component.get_transform and
		// Transform.get_position icalls. Used instead of reading the
		// MonsterNetworkSync.position SyncVar — the SyncVar is only meaningful
		// on remote clients; for the host (server) the field stays at (0,0,0)
		// because the host never receives its own SyncVars.
		bool ReadLivePosition(void* component, Vector3& out)
		{
			if (!IsValidPtr(component))
				return false;
			if (!Pointers.Component_get_transform || !Pointers.Transform_get_position)
				return false;
			void* transform = Pointers.Component_get_transform(component, nullptr);
			if (!IsValidPtr(transform))
				return false;
			Pointers.Transform_get_position(&out, transform, nullptr);
			return true;
		}

		void Collect(std::vector<MonsterInfo>& out)
		{
			out.clear();

			auto* mgr = Pointers.AIManager.Get();
			if (!IsValidPtr(mgr))
				return;

			auto* localPlayer = Pointers.LocalPlayer.Get();
			if (!IsValidPtr(localPlayer))
				return;

			Vector3 localPos{};
			if (!ReadLivePosition(localPlayer, localPos))
				return;

			const auto view = ViewList<AIController_o>(mgr->allAIControllers);
			if (!view.items)
				return;

			for (int32_t i = 0; i < view.size; ++i)
			{
				auto* ctrl = view.items[i];
				if (!IsValidPtr(ctrl))
					continue;

				auto* sync = ctrl->_MonsterNetworkSync_k__BackingField;
				if (!IsValidPtr(sync))
					continue;

				// Read the monster's actual world position from its Transform.
				// We use AIController as the Component to ask (it lives on the
				// same GameObject as MonsterNetworkSync); either works.
				Vector3 pos{};
				if (!ReadLivePosition(ctrl, pos))
					continue;

				const float dx = pos.x - localPos.x;
				const float dy = pos.y - localPos.y;
				const float dz = pos.z - localPos.z;
				// Empirical: 1 game unit ≈ 0.1 m in Labyrinthine (positions
				// look ~10× larger than perceived in-world distance).
				constexpr float kUnitToMeter = 0.1f;
				const float distance = std::sqrt(dx * dx + dy * dy + dz * dz) * kUnitToMeter;

				if (distance > s_Settings.maxDistanceM)
					continue;

				out.push_back({
				    .name     = DisplayName(sync),
				    .distance = distance,
				    .chasing  = sync->_IsChasingPlayer_k__BackingField,
				});
			}
		}

		void DrawOverlay()
		{
			if (!s_Settings.enabled)
				return;

			static thread_local std::vector<MonsterInfo> infos;
			Collect(infos);

			// Sort nearest first.
			std::sort(infos.begin(), infos.end(),
			    [](const MonsterInfo& a, const MonsterInfo& b) { return a.distance < b.distance; });

			const auto& io = ImGui::GetIO();
			ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 10.0f, 10.0f),
			    ImGuiCond_Always, ImVec2(1.0f, 0.0f));
			ImGui::SetNextWindowBgAlpha(0.55f);

			constexpr ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration
			    | ImGuiWindowFlags_AlwaysAutoResize
			    | ImGuiWindowFlags_NoNav
			    | ImGuiWindowFlags_NoFocusOnAppearing
			    | ImGuiWindowFlags_NoSavedSettings;

			if (ImGui::Begin("##MonsterAwareness", nullptr, flags))
			{
				if (infos.empty())
				{
					ImGui::TextDisabled("No monsters within %.0f m", s_Settings.maxDistanceM);
				}
				else
				{
					for (const auto& m : infos)
					{
						if (m.chasing)
							ImGui::TextColored(ImVec4(1.0f, 0.35f, 0.35f, 1.0f),
							    "%s  %.1fm  CHASING", m.name.c_str(), m.distance);
						else
							ImGui::Text("%s  %.1fm", m.name.c_str(), m.distance);
					}
				}
			}
			ImGui::End();
		}
	}

	void Init()
	{
		// Priority 0 — runs after the menu's priority -1 callback. Self-gates
		// on s_Settings.enabled so it's effectively dormant when off.
		Renderer::AddDXCallback(DrawOverlay, 0);
	}

	Settings& GetSettings()
	{
		return s_Settings;
	}

	void DrawSettingsTab()
	{
		if (ImGui::BeginTabItem("Monsters"))
		{
			ImGui::Checkbox("Enable awareness HUD", &s_Settings.enabled);
			ImGui::SliderFloat("Max distance (m)", &s_Settings.maxDistanceM,
			    5.0f, 200.0f, "%.0f");
			ImGui::TextDisabled("World markers deferred to v1.5 — side panel only.");
			ImGui::EndTabItem();
		}
	}
}
