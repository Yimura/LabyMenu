#pragma once
#include "../base/Array.hpp"
#include "../il2cpp/il2cpp.hpp"

#include <cstdint>

namespace YimMenu
{
    struct System_Collections_Generic_Dictionary_int__LobbyDummy__VTable
    {
        VirtualInvokeData _0_Equals;
        VirtualInvokeData _1_Finalize;
        VirtualInvokeData _2_GetHashCode;
        VirtualInvokeData _3_ToString;
        VirtualInvokeData _4_get_Item;
        VirtualInvokeData _5_set_Item;
        VirtualInvokeData _6_System_Collections_Generic_IDictionary_TKey_TValue__get_Keys;
        VirtualInvokeData _7_System_Collections_Generic_IDictionary_TKey_TValue__get_Values;
        VirtualInvokeData _8_ContainsKey;
        VirtualInvokeData _9_Add;
        VirtualInvokeData _10_Remove;
        VirtualInvokeData _11_unknown;
        VirtualInvokeData _12_unknown;
        VirtualInvokeData _13_System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___get_IsReadOnly;
        VirtualInvokeData _14_System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Add;
        VirtualInvokeData _15_Clear;
        VirtualInvokeData _16_System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Contains;
        VirtualInvokeData _17_System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___CopyTo;
        VirtualInvokeData _18_System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Remove;
        VirtualInvokeData _19_System_Collections_Generic_IEnumerable_System_Collections_Generic_KeyValuePair_TKey_TValue___GetEnumerator;
        VirtualInvokeData _20_System_Collections_IEnumerable_GetEnumerator;
        VirtualInvokeData _21_System_Collections_IDictionary_get_Item;
        VirtualInvokeData _22_System_Collections_IDictionary_set_Item;
        VirtualInvokeData _23_System_Collections_IDictionary_get_Keys;
        VirtualInvokeData _24_System_Collections_IDictionary_Contains;
        VirtualInvokeData _25_System_Collections_IDictionary_Add;
        VirtualInvokeData _26_System_Collections_IDictionary_GetEnumerator;
        VirtualInvokeData _27_System_Collections_IDictionary_Remove;
        VirtualInvokeData _28_System_Collections_ICollection_CopyTo;
        VirtualInvokeData _29_unknown;
        VirtualInvokeData _30_System_Collections_ICollection_get_SyncRoot;
        VirtualInvokeData _31_System_Collections_ICollection_get_IsSynchronized;
        VirtualInvokeData _32_TryGetValue;
        VirtualInvokeData _33_System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Keys;
        VirtualInvokeData _34_System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Values;
        VirtualInvokeData _35_get_Count;
        VirtualInvokeData _36_unknown;
        VirtualInvokeData _37_unknown;
        VirtualInvokeData _38_GetObjectData;
        VirtualInvokeData _39_OnDeserialization;
    };

    class System_Collections_Generic_Dictionary_int__LobbyDummy__Fields
    {
    public:
        Array<int32_t> *buckets;
        struct System_Collections_Generic_Dictionary_Entry_TKey__TValue__array *entries;
        int32_t count;
        int32_t version;
        int32_t freeList;
        int32_t freeCount;
        struct System_Collections_Generic_IEqualityComparer_TKey__o *comparer;
        struct System_Collections_Generic_Dictionary_KeyCollection_TKey__TValue__o *keys;
        struct System_Collections_Generic_Dictionary_ValueCollection_TKey__TValue__o *values;
        Il2CppObject *_syncRoot;
    };

    struct System_Collections_Generic_Dictionary_int__LobbyDummy__c
    {
        Il2CppClass_1 _1;
        void *static_fields;
        Il2CppRGCTXData *rgctx_data;
        Il2CppClass_2 _2;
        System_Collections_Generic_Dictionary_int__LobbyDummy__VTable vtable;
    };

    // template<typename K, typename T>
    struct System_Collections_Generic_Dictionary_int__LobbyDummy__o
    {
        System_Collections_Generic_Dictionary_int__LobbyDummy__c *klass;
        void *monitor;
        System_Collections_Generic_Dictionary_int__LobbyDummy__Fields fields;
    };
}
