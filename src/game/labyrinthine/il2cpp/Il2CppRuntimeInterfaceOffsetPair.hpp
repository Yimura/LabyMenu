#pragma once
#include "Il2CppClass.hpp"

#include <cstdint>

namespace YimMenu
{
	struct Il2CppRuntimeInterfaceOffsetPair
	{
		Il2CppClass* interfaceType;
		int32_t offset;
	};
}
