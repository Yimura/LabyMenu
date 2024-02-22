#pragma once
#include "../il2cpp/il2cpp.hpp"
#include "Array.hpp"
#include "Iterator.hpp"

namespace YimMenu
{
	template<typename T>
	class ListFields
	{
	public:
		Array<T>* _items;
		int32_t _size;
		int32_t _version;
		Il2CppObject* _syncRoot;
	};
	static_assert(sizeof(ListFields<int>) == 0x18);

	template<typename T>
	class List
	{
	private:
		void* klass;
		void* monitor;
		ListFields<T> fields;

	public:
		inline auto begin()
		{
			if ((std::uintptr_t)fields._items == 0xFFFFFFFFFFFFFFDF)
			{
				return Iterator<T>(nullptr);
			}
			return (*fields._items).begin();
		}

		inline auto end()
		{
			if ((std::uintptr_t)fields._items == 0xFFFFFFFFFFFFFFDF)
			{
				return Iterator<T>(nullptr);
			}
			return (*fields._items).end();
		}

		inline auto data()
		{
			if (fields._items == 0xFFFFFFFFFFFFFFDF)
			{
				return nullptr;
			}
			return (*fields._items).data();
		}

		inline auto size() const
		{
			if (fields._items == 0xFFFFFFFFFFFFFFDF)
			{
				return 0;
			}
			return (*fields._items).size();
		}

	};
	static_assert(sizeof(List<int>) == 0x28);
}
