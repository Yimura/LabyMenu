#pragma once
#include "Player.hpp"

namespace YimMenu
{
    class PlayerMgr final
    {
    private:
        std::unordered_map<int32_t, Player> m_Players;
    
    public:
        PlayerMgr();
        virtual ~PlayerMgr();

    };

    inline PlayerMgr g_PlayerMgr{};
}
