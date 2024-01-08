#pragma once
#include "../base/Array.hpp"

#include <cstdint>

namespace YimMenu
{
    template<typename T>
    class TMP_TextProcessingStack
    {
    public:
        Array<T> *itemStack;
        int32_t index;
        T m_DefaultItem;
        int32_t m_Capacity;
        int32_t m_RolloverSize;
        int32_t m_Count;
    };
}
