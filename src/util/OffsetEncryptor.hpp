#pragma once
#include <cstddef>
#include <cstdint>
#include "CompileTimeRandom.hpp"

namespace YimMenu
{
    #define ENCRYPT_OFFSET(T, member) OffsetEncryptor(offsetof(T, member), RAND_NEXT)

    class OffsetEncryptor
    {
    public:
        consteval OffsetEncryptor(std::size_t offset, std::uint64_t key);
        virtual ~OffsetEncryptor() = default;

        template<typename T = void*>
        T Decrypt(void* baseAddr) const;
        template<typename T = void*>
        T Decrypt(std::uintptr_t baseAddr = 0) const;

    private:
        std::size_t m_Offset;
        std::uint64_t m_Key;

    };

    inline consteval OffsetEncryptor::OffsetEncryptor(std::size_t offset, std::uint64_t key)
    {
        m_Key = key;
        m_Offset = offset ^ m_Key;
    }

    template<typename T>
    inline T OffsetEncryptor::Decrypt(void* baseAddr) const
    {
        return Decrypt<T>(reinterpret_cast<std::uintptr_t>(baseAddr));
    }

    template<typename T>
    inline T OffsetEncryptor::Decrypt(std::uintptr_t baseAddr) const
    {
        return reinterpret_cast<T>(baseAddr + (m_Key ^ m_Offset));
    }
}
