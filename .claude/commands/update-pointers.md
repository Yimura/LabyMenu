# Update Game Pointers

Verify and update the byte patterns in `src/game/pointers/Pointers.cpp` against the current GameAssembly.dll loaded in Ghidra.

## Scope

$ARGUMENTS

If no specific pointers are given, verify ALL active (non-commented) patterns in `Pointers.cpp`.

## Steps

1. **Read `src/game/pointers/Pointers.cpp` and `Pointers.hpp`** to understand the current patterns, what they resolve to, and how they're used (Add/Sub/Rip offsets, SimpleStaticWrapper vs raw pointer, etc.).

2. **Search each byte pattern in Ghidra** using `search_byte_patterns` on `GameAssembly.dll`. Use `FF` mask for literal bytes and `00` mask for wildcard (`??`) bytes. Record which patterns match and which are broken (no matches).

3. **For broken patterns**, find the corresponding function in Ghidra:
   - Use `search_functions` to locate the function by its IL2CPP name (e.g. `Mirror.NetworkManager$$SetupServer`, `LobbyManager$$Awake`).
   - Use `disassemble_function` to get the assembly.
   - Use `read_memory` to get raw bytes for pattern construction.

4. **Construct new unique patterns**:
   - Include enough context bytes to ensure uniqueness (verify with `search_byte_patterns` - must return exactly 1 match).
   - Use `??` wildcards for RIP-relative offsets in MOV/LEA instructions (the 4 bytes after `48 8B 05`, `48 8D 0D`, etc.).
   - Do NOT wildcard register+displacement encodings like `B8 00 00 00` in `MOV RCX, [RAX+0xB8]` - these are fixed struct offsets.
   - Prefer patterns that encode game-specific field offsets for stability across minor updates.

5. **Verify static field offsets** for SimpleStaticWrapper pointers:
   - IL2CPP stores class static fields at `TypeInfo + 0xB8` (pointer to static fields struct).
   - The singleton instance may be at any offset within that struct (not always 0x0).
   - Check the actual offset by reading the disassembly (e.g. `MOV RCX, [RCX + 0x10]` means offset 0x10).
   - If the offset differs from what `SimpleStaticWrapper` expects, update the `FieldOffset` template parameter in `Pointers.hpp`.

6. **Calculate Sub/Add offsets** for hook pointers (like SetupServer):
   - The pattern match address minus the function entry address gives the Sub offset.
   - Use `get_function_by_address` to confirm the function entry point.

7. **Update the code**:
   - Update patterns in `Pointers.cpp`.
   - Update Add/Sub/Rip calculations in the scanner callbacks.
   - Update `SimpleStaticWrapper` field offsets in `Pointers.hpp` if needed.

8. **Report results** in a table showing each pointer's status (OK/UPDATED), old vs new pattern, and any structural changes.

## Pattern format reference

Patterns use hex bytes separated by spaces, with `??` for wildcards:
```cpp
constexpr auto name = Pattern<"48 8B 05 ?? ?? ?? ?? 48 8B 90 B8 00 00 00">("Description");
```

## SimpleStaticWrapper chain

The pointer dereference chain is: `*TypeInfo -> +0xB8 (static_fields ptr) -> +FieldOffset -> instance`. The `FieldOffset` template parameter (default 0) controls the offset within static_fields where the instance pointer lives.
