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

	// Comments above each slot preserve the dump's original `_N_Name` form.
	struct ConnectionDebugger_VTable
	{
		// _0_Equals
		VTableSlot<bool(Il2CppObject*)>     Equals;
		// _1_Finalize
		VTableSlot<void()>                  Finalize;
		// _2_GetHashCode
		VTableSlot<int32_t()>               GetHashCode;
		// _3_ToString
		VTableSlot<System_String_o*()>      ToString;
	};

	struct ConnectionDebugger_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		ConnectionDebugger_VTable vtable;
	};
}
