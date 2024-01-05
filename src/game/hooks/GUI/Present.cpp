#include "game/hooks/Hooks.hpp"
#include "core/hooking/DetourHook.hpp"
#include "core/renderer/Renderer.hpp"

namespace YimMenu::Hooks
{
    HRESULT SwapChain::Present(IDXGISwapChain* this_, UINT sync_interval, UINT flags)
    {
        if (g_Running)// && ((flags & (UINT)DXGI_PRESENT_TEST) != (UINT)DXGI_PRESENT_TEST))
        {
            static auto ensureRendererIsSetup = (Renderer::Init(this_), true);

            Renderer::OnPresent();
        }

        return BaseHook::Get<SwapChain::Present, DetourHook<decltype(&Present)>>()->Original()(this_, sync_interval, flags);
    }
}
