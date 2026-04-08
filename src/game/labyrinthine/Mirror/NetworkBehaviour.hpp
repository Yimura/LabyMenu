#pragma once
#include "../UnityEngine/MonoBehaviour.hpp"

namespace YimMenu
{
    class Mirror_NetworkBehaviour_Fields : public UnityEngine_MonoBehaviour_Fields
    {
    public:
        int32_t syncDirection;
        int32_t syncMode;
        float syncInterval;
        double lastSyncTime;
        struct System_Collections_Generic_List_SyncObject__o *syncObjects;
        struct Mirror_NetworkIdentity_o *_netIdentity_k__BackingField;
        uint8_t _ComponentIndex_k__BackingField;
        uint64_t syncVarDirtyBits;
        uint64_t syncObjectDirtyBits;
        uint64_t syncVarHookGuard;
    };
    static_assert(sizeof(Mirror_NetworkBehaviour_Fields) == 0x68);
}
