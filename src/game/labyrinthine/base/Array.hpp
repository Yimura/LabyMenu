#pragma once
#include "../il2cpp/il2cpp.hpp"
#include "Iterator.hpp"

namespace YimMenu
{
	template<typename T>
	class Array
	{
	private:
		Il2CppObject obj;
		Il2CppArrayBounds* bounds;
		std::size_t m_ItemCount;
		T* m_Items[65535];

	public:
		T &operator [] (int i) 
    	{
        	return (*m_Items)[i];
    	}

    	const T &operator [] (int i) const 
    	{
        	return (*m_Items)[i];
    	}

		Iterator<T> begin()
		{
			if (this == nullptr || m_Items == nullptr)
			{
				return Iterator<T>(nullptr);
			}
			return Iterator(&(*m_Items)[0]);
		}

		Iterator<T> end()
		{
			if (this == nullptr || m_Items == nullptr)
			{
				return Iterator<T>(nullptr);
			}
			return Iterator(&(*m_Items)[m_ItemCount]);
		}

		T* data()
		{
			if (this == nullptr || m_Items == nullptr)
			{
				return Iterator<T>(nullptr);
			}
			return *m_Items;
		}

		std::size_t size() const
		{
			if (this == nullptr)
			{
				return 0;
			}
			return m_ItemCount;
		}
	};
	static_assert(sizeof(Array<int>) == 0x80018);
}
