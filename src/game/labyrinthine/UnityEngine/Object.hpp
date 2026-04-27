#pragma once
#include "../il2cpp/VTableSlot.hpp"
#include "../il2cpp/il2cpp.hpp"

namespace YimMenu
{
	struct System_String_o;

	class UnityEngine_Object_Fields
	{
		void* klass;
		void* monitor;
		void* m_CachedPtr;
	};

	// VTable signatures: refine VTableSlot<...> per slot when invoking; defaults
	// reflect the System.Object base methods that every IL2CPP type carries.
	// Comments above each slot preserve the dump's original `_N_Name` form so
	// the slot index is recoverable.
	struct UnityEngine_Object_VTable
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

	struct UnityEngine_Object_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		UnityEngine_Object_VTable vtable;
	};
}
