#pragma once
#include "Il2CppClass.hpp"
#include "Il2CppRGCTXData.hpp"

namespace YimMenu
{
	using Il2CppMethodPointer = void (*)();
	struct Il2CppClass;

	struct MethodInfo
	{
		Il2CppMethodPointer methodPointer;
		void* invoker_method;
		const char* name;
		Il2CppClass* klass;
		const Il2CppType* return_type;
		const void* parameters;
		union {
			const Il2CppRGCTXData* rgctx_data;
			const void* methodMetadataHandle;
		};
		union {
			const void* genericMethod;
			const void* genericContainerHandle;
		};
		uint32_t token;
		uint16_t flags;
		uint16_t iflags;
		uint16_t slot;
		uint8_t parameters_count;
		uint8_t bitflags;
	};
}
