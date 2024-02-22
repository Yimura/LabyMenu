#pragma once
#include "../base/List.hpp"

#include <cstdint>

namespace YimMenu
{
    struct TMP_Text_TextBackingContainer
    {
        Array<int32_t> *m_Array;
        int32_t m_Count;
    };
}
