#include "Renderer.hpp"

#include "game/pointers/Pointers.hpp"

#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui.h>

namespace YimMenu
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	void Renderer::DestroyImpl()
	{
		if (m_SwapChain && m_Device && m_DeviceContext)
		{
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();

			m_RenderTarget->Release();
			m_BlendState->Release();
		}
	}

	bool Renderer::InitImpl(IDXGISwapChain* swapchain)
	{
		if (m_SwapChain = swapchain; !m_SwapChain)
		{
			LOG(WARNING) << "SwapChain pointer is invalid!";

			return false;
		}

		if (const auto result = m_SwapChain->GetDevice(__uuidof(ID3D11Device), reinterpret_cast<void**>(&m_Device)); result < 0)
		{
			LOG(WARNING) << "Failed to get D3D Device with result: [" << result << "]";

			return false;
		}
		m_Device->GetImmediateContext(&m_DeviceContext);

		if (!CreateRenderTarget() || !CreateBlendState())
		{
			return false;
		}

		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		// never returns false, useless to check return
		ImGui_ImplDX11_Init(m_Device, m_DeviceContext);
		ImGui_ImplWin32_Init(Pointers.Hwnd);

		LOG(INFO) << "Renderer has finished initializing.";
		return true;
	}

	bool Renderer::AddDXCallbackImpl(DXCallback&& callback, std::uint32_t priority)
	{
		return m_DXCallbacks.insert({priority, callback}).second;
	}

	void Renderer::AddWindowProcedureCallbackImpl(WindowProcedureCallback&& callback)
	{
		return m_WindowProcedureCallbacks.push_back(callback);
	}

	void Renderer::OnPresentImpl()
	{
		Renderer::NewFrame();
		for (const auto& callback : m_DXCallbacks | std::views::values)
			callback();
		Renderer::EndFrame();
	}

	LRESULT Renderer::WndProcImpl(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		for (const auto& callback : m_WindowProcedureCallbacks)
			callback(hwnd, msg, wparam, lparam);

		return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	}

	void Renderer::PreResizeImpl()
	{
		if (m_RenderTarget)
			m_RenderTarget->Release();

		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	void Renderer::PostResizeImpl()
	{
		CreateRenderTarget();
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void Renderer::NewFrameImpl()
	{
		m_DeviceContext->OMSetBlendState(m_BlendState, m_BlendColor, 0xffffffff);

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void Renderer::EndFrameImpl()
	{
		ImGui::Render();
		m_DeviceContext->OMSetRenderTargets(1, &m_RenderTarget, nullptr);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		m_DeviceContext->OMSetBlendState(m_BlendState, m_BlendColor, 0xffffffff);
	}

	bool Renderer::CreateRenderTarget()
	{
		ID3D11Texture2D* backBuffer = nullptr;

		if (FAILED(m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
		{
			LOG(WARNING) << "Couldn't retrieve the BackBuffer of the SwapChain!";
			return false;
		}

		if (FAILED(m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTarget)))
		{
			LOG(WARNING) << "Couldn't create the RenderTargetView!";
			return false;
		}
		backBuffer->Release();
		return true;
	}

	bool Renderer::CreateBlendState()
	{
		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

		/*create blend for alpha fixing!!*/
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		if (FAILED(m_Device->CreateBlendState(&blendDesc, &m_BlendState)))
		{
			LOG(FATAL) << "Could not create the BlendState!";
			return false;
		}

		return true;
	}
}
