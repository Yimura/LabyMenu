#include "game/hooks/Hooks.hpp"
#include "core/renderer/Renderer.hpp"
#include "game/pointers/Pointers.hpp"

namespace YimMenu::Hooks
{
    LRESULT Window::WndProc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
    {
        if (g_Running)
        {
            Renderer::WndProc(hwnd, umsg, wparam, lparam);
        }
        return CallWindowProcW(Pointers.OgWndProc, hwnd, umsg, wparam, lparam);
    }
}
