#pragma once
#include "Il2CppClass.hpp"
#include "Il2CppType.hpp"
#include "MethodInfo.hpp"
#include "VTableSlot.hpp"
#include "VirtualInvokeData.hpp"

namespace YimMenu
{
    using il2cpp_array_size_t = std::uintptr_t;
    using il2cpp_array_lower_bound_t = std::int32_t;
    struct Il2CppArrayBounds
    {
        il2cpp_array_size_t length;
        il2cpp_array_lower_bound_t lower_bound;
    };

    using Il2CppObject = char[0x10];

    // Forward decl used by every per-class _VTable's _3_ToString slot.
    struct System_String_o;

    // Returns the typed klass pointer for an IL2CPP managed object.
    // `klass` is always at offset 0 of any managed object; reading via
    // reinterpret_cast bypasses C++ access controls (some `_o` types declare
    // klass private).
    //
    // Usage: Klass<Mirror_NetworkBehaviour_c>(nb)->vtable.OnStartClient(nb);
    template<typename Klass_t, typename Obj>
    inline Klass_t* Klass(Obj* obj)
    {
        return *reinterpret_cast<Klass_t**>(obj);
    }
}
