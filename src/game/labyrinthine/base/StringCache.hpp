#pragma once
#include <unordered_map>

namespace YimMenu
{
    class String;
    class StringCache
    {
    private:
        std::unordered_map<const String*, std::string> m_Cache;

    public:
        const std::string& Get(const String* owner);
        
    };
    inline StringCache g_StringCache{};
}
