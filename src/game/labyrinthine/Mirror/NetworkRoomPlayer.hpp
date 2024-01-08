#pragma once
#include "NetworkBehaviour.hpp"

namespace YimMenu
{
    class Mirror_NetworkRoomPlayer_Fields : public Mirror_NetworkBehaviour_Fields
    {
    public:
        bool showRoomGUI;
        bool readyToBegin;
        int32_t index;
    };

    struct Mirror_NetworkRoomPlayer_o
    {
        void *klass;
        void *monitor;
        Mirror_NetworkRoomPlayer_Fields fields;
    };
}
