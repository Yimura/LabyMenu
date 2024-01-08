#include "StringCache.hpp"
#include "String.hpp"

namespace YimMenu
{
    const std::string& StringCache::Get(const String* owner)
    {
        if (const auto& it = m_Cache.find(owner); it != m_Cache.end())
        {
            return it->second;
        }
        if (owner->IsEmpty())
        {
            static std::string UnkStr("unknown");
            return UnkStr;
        }
        return m_Cache.insert({ owner, owner->GetUnicodeString() }).first->second;
    }
}
