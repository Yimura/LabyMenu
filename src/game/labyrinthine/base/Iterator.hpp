#pragma once

namespace YimMenu
{
    template<typename T>
    class Iterator
    {
    private:
        T* m_Ptr;

    public:
        Iterator(T* ptr) :
            m_Ptr(ptr)
        {}

        T& operator*() const
        { return *m_Ptr; }

        T* operator->()
        { return m_Ptr; }

        Iterator<T>& operator++()
        {
            m_Ptr++;
            return *this;
        }

        Iterator<T> operator++(int)
        {
            Iterator<T> copy = m_Ptr;
            ++(*this);
            return copy;
        }

        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_Ptr == b.m_Ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_Ptr != b.m_Ptr; }; 
    };
}
