#include "String.hpp"

#include <Windows.h>

namespace YimMenu
{
	bool String::IsEmpty() const
	{
		return reinterpret_cast<std::uintptr_t>(this) < 0x10000
			|| m_StringLength <= 0
			|| m_StringLength > 1024;
	}

	std::string String::str() const
	{
		if (IsEmpty())
			return "unknown";

		// Use WideCharToMultiByte for reliable UTF-16 -> UTF-8 conversion
		// bounded by m_StringLength (no null-terminator dependency)
		int size = WideCharToMultiByte(
			CP_UTF8, 0,
			reinterpret_cast<const wchar_t*>(&m_FirstChar), m_StringLength,
			nullptr, 0, nullptr, nullptr);

		if (size <= 0)
			return "unknown";

		std::string result(size, '\0');
		WideCharToMultiByte(
			CP_UTF8, 0,
			reinterpret_cast<const wchar_t*>(&m_FirstChar), m_StringLength,
			result.data(), size, nullptr, nullptr);

		return result;
	}
}
