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
		inline bool IsValid() const
		{
			auto addr = reinterpret_cast<std::uintptr_t>(fields._items);
			return addr > 0x10000 && addr < 0x7FFFFFFFFFFF && fields._size > 0;
		}

		inline auto begin()
		{
			if (!IsValid())
				return Iterator<T>(nullptr);
			return (*fields._items).begin();
		}

		inline auto end()
		{
			if (!IsValid())
				return Iterator<T>(nullptr);
			// Use _size (logical count), NOT the backing array capacity.
			// Entries past _size are uninitialized garbage.
			return Iterator<T>(&(*fields._items).data()[fields._size]);
		}

		inline auto data()
		{
			if (!IsValid())
				return (T*)nullptr;
			return (*fields._items).data();
		}

		inline auto size() const
		{
			if (!IsValid())
				return 0;
			return fields._size;
		}

	};
	static_assert(sizeof(List<int>) == 0x28);
}
