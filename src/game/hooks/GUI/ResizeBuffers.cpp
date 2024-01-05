#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "core/renderer/Renderer.hpp"

namespace YimMenu::Hooks
{
    HRESULT SwapChain::ResizeBuffers(IDXGISwapChain* this_, UINT buffer_count, UINT width, UINT height, DXGI_FORMAT new_format, UINT swapchain_flags)
    {
        if (g_Running)
		{
			Renderer::PreResize();
			const auto result = BaseHook::Get<SwapChain::ResizeBuffers, DetourHook<decltype(&ResizeBuffers)>>()->Original()(this_, buffer_count, width, height, new_format, swapchain_flags);
			Renderer::PostResize();
			return result;
		}
		
		return BaseHook::Get<SwapChain::Present, DetourHook<decltype(&ResizeBuffers)>>()->Original()(this_, buffer_count, width, height, new_format, swapchain_flags);
    }
}
