#pragma once
#include "Il2CppClass.hpp"

namespace YimMenu
{
	// Strongly-typed virtual-method slot. Inherits VirtualInvokeData so the
	// layout (16 bytes: methodPtr + MethodInfo*) is identical by construction —
	// it can be dropped directly into a class' vtable metadata. The signature
	// lives in the type, so call sites don't repeat parameter types — just pass
	// `this_` and the managed args.
	//
	// IL2CPP convention: every compiled method takes a trailing `const MethodInfo*`
	// as its last argument. The slot reads it from its own `method` field and
	// appends it automatically.
	//
	// Example:
	//   // _2_GetHashCode
	//   VTableSlot<int32_t()> GetHashCode;          // declared in vtable struct
	//   int hc = obj->klass->vtable.GetHashCode(obj); // called like a function
	template<typename Sig>
	struct VTableSlot;

	template<typename Ret, typename... Args>
	struct VTableSlot<Ret(Args...)> : VirtualInvokeData
	{
		template<typename This>
		Ret operator()(This* this_, Args... args) const
		{
			using Fn = Ret(*)(This*, Args..., const MethodInfo*);
			return reinterpret_cast<Fn>(methodPtr)(this_, args..., method);
		}
	};
}
