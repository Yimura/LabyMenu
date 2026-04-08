# Verify Game Structures

Verify that the C++ structure definitions under `src/game/labyrinthine/` are up-to-date against `reversing/il2cpp.h` and Ghidra.

## Scope

$ARGUMENTS

If no specific files/classes are given, verify ALL `.hpp` files under `src/game/labyrinthine/`.

## Steps

1. **Read the C++ headers** in `src/game/labyrinthine/` to understand current field layouts and `static_assert` sizes.

2. **Cross-reference against `reversing/il2cpp.h`** by searching for the corresponding `_Fields` struct (e.g. `PlayerNetworkSync_Fields`, `Mirror_NetworkBehaviour_Fields`). Compare field names, types, and order.

3. **Query Ghidra** for the `_o` struct layout using `get_struct_layout` on `GameAssembly.dll` to get the authoritative total size and field offsets.

4. **Identify all differences**: added fields, removed fields, reordered fields, type changes, renamed fields, and size mismatches.

5. **Check inheritance chain impact**: If a base class changed (e.g. `MonoBehaviour_Fields`, `Mirror_NetworkBehaviour_Fields`), ALL derived classes shift. Verify every descendant's `static_assert`.

6. **Update the C++ headers** to match il2cpp.h exactly. For each struct:
   - Match the field order from il2cpp.h
   - Use the types from il2cpp.h
   - Update the `static_assert` to match the Ghidra `_o` total size
   - In the C++ codebase, the `_o` struct inherits from the `_Fields` chain which includes `klass`+`monitor` (baked into `UnityEngine_Object_Fields`), so the C++ struct size equals the Ghidra `_o` size directly.

7. **Fix any active code** that references removed/renamed fields (search `src/` for usages).

8. **Build the project** to verify all `static_assert`s pass.

## Size calculation reference

The C++ headers use a flattened model where `UnityEngine_Object_Fields` includes `klass`(8) + `monitor`(8) + `m_CachedPtr`(8). All game classes inherit this chain, so their C++ `sizeof()` equals the Ghidra `_o` struct size (which includes `klass` + `monitor` + `fields`).

## Key il2cpp.h search patterns

- Search `struct ClassName_Fields :` to find the field definition
- Search `struct ClassName_o {` to find the wrapper with klass/monitor/fields
- Search `struct ClassName_StaticFields` to find static fields (singleton instances, etc.)
