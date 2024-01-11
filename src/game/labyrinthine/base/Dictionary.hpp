#pragma once
#include "Array.hpp"

namespace YimMenu
{
    template<typename K, typename T>
    class Dictionary;

    template<typename K>
    class KeysCollection
    {
    private:
        Dictionary<K, int>* m_Dictionary;

    public:
        template<typename K, typename T>
        KeysCollection(Dictionary<K, T>* dictionary) :
            m_Dictionary(reinterpret_cast<decltype(m_Dictionary)>(dictionary))
        {}

        K operator[](int i)
        {
            auto entries = m_Dictionary->m_Entries;
            if (!entries)
                return K();
            return (*entries)[i].key;
        }

        const K operator[](int i) const
        {
            auto entries = m_Dictionary->m_Entries;
            if (!entries)
                return K();
            return (*entries)[i].key;
        }

        int Count()
        {
            return m_Dictionary->Count();
        }
    };

    template<typename T>
    class ValueCollection
    {
    private:
        Dictionary<int, T>* m_Dictionary;

    public:
        template<typename K, typename T>
        ValueCollection(Dictionary<K, T>* dictionary) :
            m_Dictionary(reinterpret_cast<decltype(m_Dictionary)>(dictionary))
        {}

        T operator[](int i)
        {
            auto entries = m_Dictionary->m_Entries;
            if (!entries)
                return T();
            return (*entries)[i].value;
        }

        const T operator[](int i) const
        {
            auto entries = m_Dictionary->m_Entries;
            if (!entries)
                return T();
            return (*entries)[i].value;
        }

        int Count() const
        {
            return m_Dictionary->Count();
        }
    };

	template<typename K, typename T>
	class Dictionary
	{
    private:
        friend class KeysCollection<K>;
        friend class ValueCollection<T>;
		struct Entry
		{
			int hashCode;
			int next;
			K key;
			T value;
		};

		void* kass;
		void* monitor;
		Array<int>* m_Buckets;
		Array<Entry>* m_Entries;
		int m_Count;
		int version;
		int freeList;
		int freeCount;
		void* comparer;
		KeysCollection<K>* m_Keys;
		ValueCollection<T>* values;
		void* _syncRoot;

    public:
		void* Comparer()
		{
			return comparer;
		}

		int Count() const
		{
			return m_Count;
		}

		KeysCollection<K> Keys()
		{
			if (!m_Keys)
				m_Keys = new KeysCollection<K>(this);
			return (*m_Keys);
		}

		ValueCollection<T> Values()
		{
			if (!values)
				values = new ValueCollection<T>(this);
			return (*values);
		}

		T operator[](K key)
		{
			int i = FindEntry(key);
			if (i >= 0)
				return (*m_Entries)[i].value;
			return T();
		}

		const T operator[](K key) const
		{
			int i = FindEntry(key);
			if (i >= 0)
				return (*m_Entries)[i].value;
			return T();
		}

		int FindEntry(K key)
		{
			for (int i = 0; i < m_Count; i++)
			{
				if ((*m_Entries)[i].key == key)
					return i;
			}
			return -1;
		}

		bool ContainsKey(K key)
		{
			return FindEntry(key) >= 0;
		}

		bool ContainsValue(T value)
		{
			for (int i = 0; i < m_Count; i++)
			{
				if ((*m_Entries)[i].hashCode >= 0 && (*m_Entries)[i].value == value)
					return true;
			}
			return false;
		}

		bool TryGetValue(K key, T* value)
		{
			int i = FindEntry(key);
			if (i >= 0)
			{
				*value = (*m_Entries)[i].value;
				return true;
			}
			*value = T();
			return false;
		}

		T GetValueOrDefault(K key)
		{
			int i = FindEntry(key);
			if (i >= 0)
			{
				return (*m_Entries)[i].value;
			}
			return T();
		}
	};
}
