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
    };
    static_assert(sizeof(Mirror_NetworkRoomPlayer_o) == 0x50);
}
