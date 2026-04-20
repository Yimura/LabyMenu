#pragma once
#include "UnityEngine/MonoBehaviour.hpp"

#include <cstdint>

namespace YimMenu
{
	// ConnectionDebugger - reads Mirror.NetworkTime.rtt each frame and stores as integer ms
	// Field offsets verified via disassembly of ConnectionDebugger$$Update
	class ConnectionDebugger_o : public UnityEngine_MonoBehaviour_Fields
	{
	public:
		int32_t _Ping_k__BackingField; // 0x20 - current ping in ms (from rtt * 1000)
		int32_t sum;                   // 0x24
		int32_t under100;             // 0x28
		int32_t above100;             // 0x2c
		int32_t above200;             // 0x30
		int32_t above500;             // 0x34
	};
	static_assert(offsetof(ConnectionDebugger_o, _Ping_k__BackingField) == 0x20);
}
