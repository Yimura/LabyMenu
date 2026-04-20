#pragma once

#include <cstdint>
#include <string>

namespace YimMenu
{
	// IL2CPP System.String layout:
	//   0x00: Il2CppObject (klass + monitor = 0x10)
	//   0x10: int32_t m_StringLength (character count, NOT byte count)
	//   0x14: char16_t m_FirstChar (start of inline UTF-16 buffer, length-prefixed NOT null-terminated)
	class String
	{
	private:
		void* klass;
		void* monitor;
		std::int32_t m_StringLength;
		char16_t m_FirstChar; // first element of inline char16_t[m_StringLength] buffer

	public:
		// Safe validity check - validates pointer range and sane length
		bool IsEmpty() const;

		// Returns a UTF-8 std::string converted from the IL2CPP UTF-16 buffer.
		// Uses m_StringLength for bounds (does NOT rely on null termination).
		// Result is computed fresh each call - caller should cache if needed.
		std::string str() const;

		// Returns pointer to the raw UTF-16 data
		const char16_t* data() const { return &m_FirstChar; }

		// Returns the character count
		int32_t length() const { return m_StringLength; }
	};
	static_assert(sizeof(String) == 0x18);
}
