#include "Hooking.hpp"

#include "BaseHook.hpp"
#include "DetourHook.hpp"
#include "VMTHook.hpp"
#include "game/hooks/Hooks.hpp"
#include "game/pointers/Pointers.hpp"
#include "core/memory/ModuleMgr.hpp"

namespace YimMenu
{
	Hooking::Hooking()
	{
		// BaseHook::Add<Hooks::Window::WndProc>(new DetourHook("WndProc", Pointers.WndProc, Hooks::Window::WndProc));

		BaseHook::Add<Hooks::SwapChain::Present>(new DetourHook("SwapChain::Present", Pointers.SwapchainVtable[Hooks::SwapChain::VMTPresentIdx], Hooks::SwapChain::Present));
		BaseHook::Add<Hooks::SwapChain::ResizeBuffers>(new DetourHook("SwapChain::ResizeBuffers", Pointers.SwapchainVtable[Hooks::SwapChain::VMTResizeBuffersIdx], Hooks::SwapChain::ResizeBuffers));

		BaseHook::Add<Hooks::Labyrinthine::NetworkMgrSetupServer>(new DetourHook("Mirror::NetworkManager::SetupServer", Pointers.NetworkMgrSetupServer, Hooks::Labyrinthine::NetworkMgrSetupServer));

		BaseHook::Add<Hooks::Labyrinthine::HasSupporterDlc>(new DetourHook("HasSupporterDlc", Pointers.HasSupporterDlc, &Hooks::Labyrinthine::HasSupporterDlc));
	}

	Hooking::~Hooking()
	{
		DestroyImpl();
	}

	bool Hooking::Init()
	{
		return GetInstance().InitImpl();
	}

	void Hooking::Destroy()
	{
		GetInstance().DestroyImpl();
	}

	bool Hooking::InitImpl()
	{
		Pointers.OgWndProc = WNDPROC(SetWindowLongPtrW(Pointers.Hwnd, GWLP_WNDPROC, LONG_PTR(&Hooks::Window::WndProc)));
		BaseHook::EnableAll();
		m_MinHook.ApplyQueued();

		return true;
	}

	void Hooking::DestroyImpl()
	{
		SetWindowLongPtrW(Pointers.Hwnd, GWLP_WNDPROC, LONG_PTR(Pointers.OgWndProc));
		BaseHook::DisableAll();
		m_MinHook.ApplyQueued();

		for (auto it : BaseHook::Hooks())
		{
			delete it;
		}
		BaseHook::Hooks().clear();
	}
}
