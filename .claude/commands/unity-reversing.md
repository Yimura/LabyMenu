# Unity IL2CPP Reversing Reference

Reference guide for reversing Unity games built with IL2CPP. Use this knowledge when analyzing GameAssembly.dll, reading game structures, and building overlays/mods.

## User input

$ARGUMENTS

## IL2CPP Object Layout

Every IL2CPP managed object follows this layout:

```
0x00: void* klass         // Il2CppClass* - pointer to class metadata
0x08: void* monitor       // Threading monitor (usually null)
0x10: <fields start>      // Instance fields begin here
```

- **`_o` suffix** = full object (klass + monitor + fields)
- **`_Fields` suffix** = just the fields portion (starts at 0x10 in the object)
- **`_c` suffix** = class metadata (Il2CppClass, TypeInfo)
- **`_StaticFields`** = static fields, accessed via `TypeInfo + 0xB8 -> deref`

### Static Instance Access Pattern (Singletons)

Most game managers are singletons. The access pattern in assembly:
```asm
MOV RAX, [TypeInfo_ptr]        ; load the Il2CppClass* (RIP-relative)
MOV RCX, [RAX + 0xB8]         ; load static fields base pointer
MOV RCX, [RCX + offset]       ; load instance at offset within static fields
```

In the codebase, this is wrapped by `SimpleStaticWrapper<T, FieldOffset>`.

## IL2CPP Strings (System.String)

Layout:
```
0x00: void* klass
0x08: void* monitor
0x10: int32_t m_StringLength   // character count (NOT byte count)
0x14: char16_t m_FirstChar     // start of inline UTF-16 buffer
```

**Critical rules:**
- Strings are **length-prefixed, NOT null-terminated**. Never use `std::u16string(&m_Data)` — it will overread.
- Always use `m_StringLength` to bound reads.
- Use `WideCharToMultiByte(CP_UTF8, ...)` with explicit length for conversion on Windows.
- Strings can be GC-relocated — don't cache by pointer across frames.

## IL2CPP Collections

### System.Collections.Generic.List\<T\>

```
0x00: klass
0x08: monitor
0x10: Array<T>* _items    // backing array (capacity >= size)
0x18: int32_t _size       // LOGICAL element count
0x1C: int32_t _version    // mutation counter
0x20: void* _syncRoot
```

**Critical:** Iterate only up to `_size`, NOT `_items->max_length`. Elements past `_size` in the backing array are **uninitialized garbage** (sentinel values like `0xFFFFFFFFFFFFFFFF`).

### Il2CppArray\<T\>

```
0x00: klass
0x08: monitor
0x10: Il2CppArrayBounds* bounds
0x18: size_t max_length    // actual element count for arrays
0x20: T items[...]         // inline element data
```

For arrays (not List backing arrays), `max_length` IS the logical count.

## Sentinel Values and Invalid Pointers

IL2CPP/Unity uses several sentinel values for uninitialized or special-state references:

| Value | Meaning |
|-------|---------|
| `0x0000000000000000` | Null reference |
| `0xFFFFFFFFFFFFFFFF` | Common uninitialized SyncVar / sentinel |
| `0xFFFFFFFFFFFFFFDF` | IL2CPP empty array sentinel |

**Validation rule for Win64:** A valid heap pointer is `> 0x10000` and `< 0x7FFFFFFFFFFF` (user-space range). Anything outside this is either null, a sentinel, or a kernel address.

## Mirror Networking (SyncVars)

Mirror is Unity's networking library used by this game. Key concepts:

### SyncVar Lifecycle
1. Object spawns on server, gets added to player list
2. `OnStartClient` fires on all clients — the object is in the list but SyncVars may NOT be populated yet
3. SyncVar data arrives asynchronously
4. `OnXxxSyncVarChanged` hook fires when data arrives — this is the "data ready" signal

**Implication:** Never assume a SyncVar field is valid just because the object exists in a list. Check for null/sentinel before accessing SyncVar-backed fields (like `clientData`).

### NetworkBehaviour Fields (base class)
```
0x20: int32_t syncDirection
0x24: int32_t syncMode
0x28: float syncInterval
0x30: double lastSyncTime
0x38: List<SyncObject>* syncObjects
0x40: NetworkIdentity* _netIdentity_k__BackingField
0x48: uint8_t _ComponentIndex_k__BackingField
0x50: uint64_t syncVarDirtyBits
0x58: uint64_t syncObjectDirtyBits
0x60: uint64_t syncVarHookGuard
```
Total size: 0x68

### NetworkIdentity Key Flags
Access via `NetworkBehaviour._netIdentity_k__BackingField`:
```
fields + 0x00: bool _isClient_k__BackingField
fields + 0x01: bool _isServer_k__BackingField
fields + 0x02: bool _isLocalPlayer_k__BackingField
fields + 0x03: bool _isOwned_k__BackingField
```

### Host/Local Player Handling
- The host's own SyncVars may not round-trip back immediately
- Use dedicated fields (e.g., `LobbyManager.mainDummy`) for the local player
- The game gates UI updates behind `NetworkClient::get_isConnected()` which checks `connectState == 2`

## Struct Source Priority

When reconstructing structs, use these sources in order:
1. **`reversing/il2cpp.h`** — generated from IL2CPP metadata, always authoritative for field order and types
2. **Ghidra MCP `search_data_types`** — same data imported via `il2cpp_header_to_ghidra.py`
3. **Disassembly verification** — verify field offsets by checking `[reg + offset]` accesses in key functions (e.g., `DeserializeSyncVars`, `OnStartClient`)

Never reconstruct structs from decompilation alone — use il2cpp.h first, verify with disasm second.

## Common Pitfalls

### Scene Transitions
During scene loads (e.g., Main Menu → Lobby), game objects and their containing lists may be:
- Partially initialized (list exists, items are garbage)
- Partially destroyed (list items point to freed objects)
- Not yet created (manager singletons are null)

**The game's approach:** Gate all access behind `NetworkClient::isConnected` and object-specific ready flags (e.g., `networkReady`, non-null `clientData`).

### Obfuscated Values
Some games use anti-cheat obfuscation (e.g., `CodeStage.AntiCheat.ObscuredTypes`):
- `ObscuredInt`, `ObscuredFloat`, etc. store encrypted values
- Reading the raw field gives garbage — must call the implicit conversion operator or replicate the XOR logic
- For READ-ONLY purposes: look at how the game's own display functions convert the value (e.g., `PlayerSave::GetLevel(experience)`)

### TMP_Text for Display Strings
`TMP_Text.m_text` (a `String*` at a deep offset in the TMP_Text class) often contains the rendered display string. This is useful when the underlying data source (like a SyncVar) isn't readily available — the UI text is already formatted and valid.

## Pattern Scanning for Singletons

To find a static instance pointer:
1. Find a function that accesses the singleton (e.g., `ClassName$$Awake` stores `this`)
2. In the disassembly, find `MOV RAX, [RIP + offset]` that loads the TypeInfo pointer
3. Use surrounding unique bytes as pattern context (field stores, specific offsets, adjacent TypeInfo loads)
4. The pattern resolves to the address holding the TypeInfo pointer
5. At runtime: `*(TypeInfo + 0xB8)` = static fields base, then `+(field offset)` = the instance

**Pattern uniqueness:** Include at least 10 non-wildcard bytes. Prefer bytes after init-flag checks (the `MOV byte [flag], 1` + TypeInfo load combo). Verify with `search_byte_patterns` that exactly 1 match exists.
