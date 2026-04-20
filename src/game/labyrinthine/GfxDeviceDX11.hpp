#pragma once
#include <cstddef>
#include <cstdint>
#include <dxgi.h>

namespace YimMenu
{
	class GfxDeviceDX11
	{
		char m_padding[0x320]; // 0x0000

	public:
		IDXGISwapChain* m_pSwapChain; // 0x0320
	};
	static_assert(sizeof(GfxDeviceDX11) == 0x328);
}
