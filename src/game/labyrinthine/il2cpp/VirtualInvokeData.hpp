#pragma once
#include "MethodInfo.hpp"

namespace YimMenu
{
    struct VirtualInvokeData
    {
        Il2CppMethodPointer methodPtr;
        const MethodInfo *method;
    };
}
