#pragma once
#include "core/hooking/BaseHook.hpp"

namespace YimMenu
{
	class Mirror_NetworkManager_o;
	class Mirror_NetworkConnection_o;
	struct Mirror_ConnectMessage
	{
	};
	class MethodInfo;
}

namespace YimMenu::Hooks
{
	namespace Labyrinthine
	{
		extern void NetworkMgrSetupServer(Mirror_NetworkManager_o* this_, const MethodInfo* method);
		extern void NetworkManager_OnServerConnectInternal(Mirror_NetworkManager_o* this_, Mirror_NetworkConnection_o* conn, Mirror_ConnectMessage connectMsg, const MethodInfo* method);
		extern void NetworkManager_OnServerDisconnect(Mirror_NetworkManager_o* this_, Mirror_NetworkConnection_o* conn, const MethodInfo* method);
	}

	namespace SwapChain
	{
		constexpr auto VMTPresentIdx       = 8;
		constexpr auto VMTResizeBuffersIdx = 13;
		extern HRESULT Present(IDXGISwapChain* this_, UINT sync_interval, UINT flags);
		extern HRESULT ResizeBuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags);
	}

	namespace Window
	{
		extern LRESULT WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
	}
}
