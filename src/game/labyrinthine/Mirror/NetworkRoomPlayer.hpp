#pragma once
#include "NetworkBehaviour.hpp"

namespace YimMenu
{
    class Mirror_NetworkRoomPlayer_o : public Mirror_NetworkBehaviour_Fields
    {
    public:
        bool showRoomGUI;
        bool readyToBegin;
        int32_t index;
        struct System_Action_bool__bool__o* _Mirror_SyncVarHookDelegate_readyToBegin;
        struct System_Action_int__int__o* _Mirror_SyncVarHookDelegate_index;
    };
    static_assert(sizeof(Mirror_NetworkRoomPlayer_o) == 0x80);
}
