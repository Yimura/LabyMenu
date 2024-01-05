#include "Pointers.hpp"

#include "core/memory/BytePatch.hpp"
#include "core/memory/ModuleMgr.hpp"
#include "core/memory/PatternScanner.hpp"
#include "util/Joaat.hpp"
#include "core/renderer/Renderer.hpp"

namespace YimMenu
{
	bool GetSwapchainVtableFromFactory()
	{
		WNDCLASSEXW windowClass;
		windowClass.cbSize = sizeof(WNDCLASSEX);
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.lpfnWndProc = DefWindowProc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = NULL;
		windowClass.hbrBackground = NULL;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = L"Yimura";
		windowClass.hIconSm = NULL;

		::RegisterClassExW(&windowClass);

		HWND window = ::CreateWindowW(windowClass.lpszClassName, L"LabyMenu", WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, NULL, NULL, windowClass.hInstance, NULL);

		const auto d3d11 = ModuleMgr::Get("d3d11.dll"_J);
		if (!d3d11)
		{
			LOG(FATAL) << "Could not grab d3d11.dll";

			::DestroyWindow(window);
			::UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		auto D3D11CreateDeviceAndSwapChain = d3d11->GetExport<long(*)(
			IDXGIAdapter*,
			D3D_DRIVER_TYPE,
			HMODULE,
			UINT,
			const D3D_FEATURE_LEVEL*,
			UINT,
			UINT,
			const DXGI_SWAP_CHAIN_DESC*,
			IDXGISwapChain**,
			ID3D11Device**,
			D3D_FEATURE_LEVEL*,
			ID3D11DeviceContext**)>("D3D11CreateDeviceAndSwapChain"_J);
		if (!D3D11CreateDeviceAndSwapChain)
		{
			LOG(FATAL) << "Failed to grab exported function D3D11CreateDeviceAndSwapChain from d3d11.dll";

			::DestroyWindow(window);
			::UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		D3D_FEATURE_LEVEL featureLevel;
		const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_11_0 };

		DXGI_RATIONAL refreshRate;
		refreshRate.Numerator = 60;
		refreshRate.Denominator = 1;

		DXGI_MODE_DESC bufferDesc;
		bufferDesc.Width = 100;
		bufferDesc.Height = 100;
		bufferDesc.RefreshRate = refreshRate;
		bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SAMPLE_DESC sampleDesc;
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		swapChainDesc.BufferDesc = bufferDesc;
		swapChainDesc.SampleDesc = sampleDesc;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 1;
		swapChainDesc.OutputWindow = window;
		swapChainDesc.Windowed = 1;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		IDXGISwapChain* swapChain;
		ID3D11Device* device;
		ID3D11DeviceContext* context;

		if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, 2, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, &featureLevel, &context) < 0)
		{
			LOG(FATAL) << "Call to D3D11CreateDeviceAndSwapChain failed";

			::DestroyWindow(window);
			::UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
			return false;
		}

		std::copy_n(*reinterpret_cast<void***>(swapChain), Pointers.SwapchainVtable.size(), Pointers.SwapchainVtable.data());

		swapChain->Release();
		swapChain = NULL;

		device->Release();	device = NULL;

		context->Release();
		context = NULL;

		::DestroyWindow(window);
		::UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);

		return true;
	}

	bool Pointers::Init()
	{
		if (!GetSwapchainVtableFromFactory())
		{
			LOG(FATAL) << "Failed to dynamically grab IDXGISwapchain";

			return false;
		}

		const auto main_module = ModuleMgr::Get("GameAssembly.dll"_J);
		if (!main_module)
		{
			LOG(FATAL) << "Could not find GameAssembly.dll.";

			return false;
		}

		auto scanner = PatternScanner(main_module);

		constexpr auto getNetworkMgrSingleTon = Pattern<"E8 ?? ?? ?? ?? 48 85 C0 0F 84 97 03 00 00 48 8B 78 58">("GetNetworkMgrSingleton");
		scanner.Add(getNetworkMgrSingleTon, [this](PointerCalculator ptr) {
			GetNetworkMgrSingleTon = ptr.Add(1).Rip().As<Functions::GetNetworkMgrSingleton>();
		});

		constexpr auto networkMgrSetupServer = Pattern<"E8 ?? ?? ?? ?? 48 8B 03 48 8B CB 48 8B 90 D0 02 00 00">("Mirror::NetworkManager::SetupServer");
		scanner.Add(networkMgrSetupServer, [this](PointerCalculator ptr) {
			NetworkMgrSetupServer = ptr.Add(1).Rip().As<void*>();
		});

		if (!scanner.Scan())
		{ 
			LOG(FATAL) << "Some patterns could not be found, unloading.";

			return false;
		}

		if (Hwnd = FindWindowW(L"UnityWndClass", nullptr); !Hwnd)
		{
			LOG(FATAL) << "Failed to grab game window"; 

			return false;
		}

		return true;
	}

	void Pointers::Restore()
	{
	}
}
