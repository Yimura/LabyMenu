#pragma once
#include "Il2CppClass.hpp"
#include "Il2CppType.hpp"
#include "MethodInfo.hpp"
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
}
