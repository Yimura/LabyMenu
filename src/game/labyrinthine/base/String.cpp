#include "String.hpp"

#include "StringCache.hpp"

#include <codecvt>
#include <locale>

namespace YimMenu
{
	bool String::IsEmpty() const
	{
		return !this || m_StringLength == 0 || m_StringLength > 1024 || m_Data == '\0';
	}

	const std::string& String::s() const
	{
		return g_StringCache.Get(this);
	}
    
	std::string String::GetUnicodeString() const
    {
        if (IsEmpty())
        {
            static std::string UnkStr("unknown");
            return UnkStr;
        }

        std::u16string source(&m_Data);
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
        std::string dest = convert.to_bytes(source);   

        return dest;
    }
}
