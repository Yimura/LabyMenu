#pragma once
#include "../UnityEngine/MonoBehaviour.hpp"

namespace YimMenu
{
    class Mirror_NetworkBehaviour_Fields : public UnityEngine_MonoBehaviour_Fields
    {
    public:
        float lastSyncTime;
        int32_t syncMode;
        float syncInterval;
        uint64_t _syncVarDirtyBits_k__BackingField;
        uint64_t syncVarHookGuard;
        struct System_Collections_Generic_List_SyncObject__o *syncObjects;
        struct Mirror_NetworkIdentity_o *netIdentityCache;
    };
    static_assert(sizeof(Mirror_NetworkBehaviour_Fields) == 0x48);
}
