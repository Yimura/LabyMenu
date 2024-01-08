#pragma once
#include <cstdint>
#include "StringCache.hpp"

namespace YimMenu
{
    class String
    {
    private:
        void *klass;
        void *monitor;
        std::int32_t m_StringLength;
        char16_t m_Data;

    public:
        bool IsEmpty() const;
        const std::string& s() const;

    private:
        std::string GetUnicodeString() const;

        friend const std::string& StringCache::Get(const String* owner);

    };
    static_assert(sizeof(String) == 0x18);
}
