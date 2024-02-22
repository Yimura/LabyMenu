#pragma once

namespace YimMenu
{
	struct MethodInfo;
	struct Il2CppType;
	struct Il2CppClass;

	union Il2CppRGCTXData {
		void* rgctxDataDummy;
		const MethodInfo* method;
		const Il2CppType* type;
		Il2CppClass* klass;
	};
}
