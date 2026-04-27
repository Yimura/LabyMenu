#pragma once
#include "NetworkBehaviour.hpp"

namespace YimMenu
{
    class Mirror_NetworkRoomPlayer_o : public Mirror_NetworkBehaviour_Fields
    {
    public:
        bool showRoomGUI;
        bool readyToBegin;
        int32_t index;
        struct System_Action_bool__bool__o* _Mirror_SyncVarHookDelegate_readyToBegin;
        struct System_Action_int__int__o* _Mirror_SyncVarHookDelegate_index;
    };
    static_assert(sizeof(Mirror_NetworkRoomPlayer_o) == 0x80);

    // Comments above each slot preserve the dump's original `_N_Name` form.
    struct Mirror_NetworkRoomPlayer_VTable
    {
        // _0_Equals
        VTableSlot<bool(Il2CppObject*)>                                Equals;
        // _1_Finalize
        VTableSlot<void()>                                             Finalize;
        // _2_GetHashCode
        VTableSlot<int32_t()>                                          GetHashCode;
        // _3_ToString
        VTableSlot<System_String_o*()>                                 ToString;
        // _4_OnValidate
        VTableSlot<void()>                                             OnValidate;
        // _5_OnSerialize
        VTableSlot<bool(Mirror_NetworkWriter_o*, bool)>                OnSerialize;
        // _6_OnDeserialize
        VTableSlot<void(Mirror_NetworkReader_o*, bool)>                OnDeserialize;
        // _7_SerializeSyncVars
        VTableSlot<bool(Mirror_NetworkWriter_o*, bool)>                SerializeSyncVars;
        // _8_DeserializeSyncVars
        VTableSlot<void(Mirror_NetworkReader_o*, bool)>                DeserializeSyncVars;
        // _9_OnStartServer
        VTableSlot<void()>                                             OnStartServer;
        // _10_OnStopServer
        VTableSlot<void()>                                             OnStopServer;
        // _11_OnStartClient
        VTableSlot<void()>                                             OnStartClient;
        // _12_OnStopClient
        VTableSlot<void()>                                             OnStopClient;
        // _13_OnStartLocalPlayer
        VTableSlot<void()>                                             OnStartLocalPlayer;
        // _14_OnStopLocalPlayer
        VTableSlot<void()>                                             OnStopLocalPlayer;
        // _15_OnStartAuthority
        VTableSlot<void()>                                             OnStartAuthority;
        // _16_OnStopAuthority
        VTableSlot<void()>                                             OnStopAuthority;
        // _17_Weaved
        VTableSlot<void()>                                             Weaved;
    };

    struct Mirror_NetworkRoomPlayer_c
    {
        Il2CppClass_1 _1;
        void* static_fields;
        Il2CppRGCTXData* rgctx_data;
        Il2CppClass_2 _2;
        Mirror_NetworkRoomPlayer_VTable vtable;
    };
}
