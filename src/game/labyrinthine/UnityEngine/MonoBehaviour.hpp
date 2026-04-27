#pragma once
#include "Object.hpp"

namespace YimMenu
{
	class UnityEngine_Component_Fields : public UnityEngine_Object_Fields
	{ };

	struct UnityEngine_Component_VTable
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

	struct UnityEngine_Component_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		UnityEngine_Component_VTable vtable;
	};

	class UnityEngine_Behaviour_Fields : public UnityEngine_Component_Fields
	{ };

	struct UnityEngine_Behaviour_VTable
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

	struct UnityEngine_Behaviour_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		UnityEngine_Behaviour_VTable vtable;
	};

	class UnityEngine_MonoBehaviour_Fields : public UnityEngine_Behaviour_Fields
	{
	public:
		struct System_Threading_CancellationTokenSource_o* m_CancellationTokenSource;
	};

	struct UnityEngine_MonoBehaviour_VTable
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

	struct UnityEngine_MonoBehaviour_c
	{
		Il2CppClass_1 _1;
		void* static_fields;
		Il2CppRGCTXData* rgctx_data;
		Il2CppClass_2 _2;
		UnityEngine_MonoBehaviour_VTable vtable;
	};
}
