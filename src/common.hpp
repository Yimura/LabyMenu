#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <AsyncLogger/Logger.hpp>
#include <MinHook.h>
#include <array>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <d3d11.h>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <windows.h>
#ifndef IMGUI_DEFINE_MATH_OPERATORS
	#define IMGUI_DEFINE_MATH_OPERATORS
#endif // IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string_view>
#include <thread>
#include <vector>

using namespace al;
#include "core/logger/LogHelper.hpp"

#undef Yield

namespace YimMenu
{
	using namespace std::chrono_literals;
	using namespace std::string_literals;

	extern std::atomic<bool> g_Running;
	extern HINSTANCE g_DllInstance;
	extern HANDLE g_MainThread;
	extern DWORD g_MainThreadId;
}
