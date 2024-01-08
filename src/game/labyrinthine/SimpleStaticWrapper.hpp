#pragma once

namespace YimMenu
{
    template<typename T>
    class StaticInternal
    {
    private:
        char m_0x0[0xB8];

    public:
        T** m_Instance;

    };

    template<typename T>
    class SimpleStaticWrapper
    {
    private:
        StaticInternal<T>** m_Internal;

    public:
        SimpleStaticWrapper() :
            m_Internal(nullptr)
        {}

        template<typename S>
        SimpleStaticWrapper(S** instance) :
            m_Internal(reinterpret_cast<StaticInternal<T>**>(instance))
        {}

        T* Get()
        {
            if (m_Internal == nullptr || *m_Internal == nullptr || (*m_Internal)->m_Instance == nullptr)
            {
                return nullptr;
            }
            return *(*m_Internal)->m_Instance;
        }
    };
    static_assert(sizeof(SimpleStaticWrapper<int>) == 0x8);
}
