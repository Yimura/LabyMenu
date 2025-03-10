#pragma once
#include "../il2cpp/il2cpp.hpp"

namespace YimMenu
{
	class Mirror_NetworkConnection_o
	{
		void* klass;
		void* monitor;
    public:
		struct System_Collections_Generic_HashSet_NetworkIdentity__o* visList;
		struct System_Collections_Generic_Dictionary_int__NetworkMessageDelegate__o* messageHandlers;
		int32_t connectionId;
		bool isAuthenticated;
		Il2CppObject* authenticationData;
		bool isReady;
		float lastMessageTime;
		struct Mirror_NetworkIdentity_o* _identity_k__BackingField;
		struct System_Collections_Generic_HashSet_NetworkIdentity__o* clientOwnedObjects;
	};
	static_assert(sizeof(Mirror_NetworkConnection_o) == 0x48);
}
