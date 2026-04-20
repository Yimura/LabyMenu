# Find DXGI Swapchain in a Binary

Locate where the DXGI swapchain is created and stored in the currently active Ghidra program. Produce a scannable byte pattern that resolves to the `IDXGISwapChain**` (pointer-to-pointer) so it can be hooked at runtime.

## User input

$ARGUMENTS

Ask the user for any missing context:
- **Renderer**: DX11, DX12, Vulkan, or unknown. If unknown, search for all and report what's found.
- **Engine**: Unity (IL2CPP / Mono), Unreal, custom, or unknown. Engine knowledge narrows the search (e.g. Unity uses `UnityPlayer.dll` for rendering, Unreal uses the main executable).
- **Binary**: Which loaded program to search (e.g. `UnityPlayer.dll`, the game exe). If not specified, check the active program.

## Strategy overview

DXGI swapchains are COM objects created via `IDXGIFactory::CreateSwapChain` (vtable +0x50) or `IDXGIFactory2::CreateSwapChainForHwnd` (vtable +0x78). The key challenge is that stripped binaries have no symbol names and load DXGI dynamically. The approach below uses **COM GUIDs as anchors** since they are embedded as constant data and survive stripping.

## Steps

### 1. Determine renderer type

Search for evidence of which graphics API is in use:

- **DX11**: Search for `"d3d11.dll"` / `"D3D11CreateDevice"` as ASCII byte patterns. Also search for the IID_ID3D11Device GUID: `db 6f 89 db 36 1f 4c 8e aa 89 53 c8 ac fa bf 7e`.
- **DX12**: Search for `"d3d12.dll"` / `"D3D12CreateDevice"` as ASCII byte patterns. Also search for the IID_ID3D12Device GUID: `34 44 16 e4 09 4a 4f 84 86 69 be a8 fd 21 83 6f`.
- **Vulkan**: Search for `"vulkan-1.dll"` / `"vkCreateInstance"` as ASCII byte patterns.
- **DXGI (shared)**: Search for `"dxgi.dll"` as an ASCII byte pattern: `64 78 67 69 2e 64 6c 6c`. This is common to both DX11 and DX12.

If the strings aren't found (encoded or constructed at runtime), fall back to GUID searches.

Report which renderers are present before continuing.

### 2. Find swapchain-related GUIDs

Search for these COM IID byte patterns (little-endian GUID encoding):

| Interface | GUID bytes |
|-----------|-----------|
| IDXGISwapChain | `a0 36 0d 31 e7 d2 0a 4c aa 04 6a 9d 23 b8 88 6a` |
| IDXGISwapChain1 | `90 a4 29 79 0d d5 76 48 83 1d 34 d8 e0 5e 68 0a` |
| IDXGISwapChain2 | `c4 2a be a8 9f 19 46 49 b3 31 79 59 9f b9 8d e7` |
| IDXGISwapChain3 | `db 9b d9 94 f8 f1 b0 4a b2 36 7d a0 17 0e da b1` |
| IDXGISwapChain4 | `71 69 c0 3a 69 95 fe 45 83 14 06 05 07 94 ef 55` |
| IDXGIFactory | `e8 d3 7a 7c 0d ac 58 45 86 0e 2d 7f 8c 43 10 a5` |
| IDXGIFactory1 | `70 bb 76 77 8e 21 48 d4 ab ba 27 d1 46 b4 64 13` |
| IDXGIFactory2 | `1c 3a c8 50 72 e0 48 4c 87 b0 36 30 fa 36 a6 d0` |
| IID_IUnknown | `00 00 00 00 00 00 00 00 c0 00 00 00 00 00 00 46` |

Use `search_byte_patterns` with full `FF` masks. Record which GUIDs exist and their addresses.

### 3. Trace from GUIDs to swapchain creation

For each found swapchain GUID:
1. Use `get_xrefs_to` on the GUID address to find code that references it (typically `QueryInterface` calls).
2. If no xrefs are found (common with RIP-relative addressing gaps in analysis), look at nearby data for related GUIDs and debug strings.
3. For GUIDs that DO have xrefs, decompile the referencing functions.

**What to look for in decompiled code:**
- `QueryInterface` pattern: `(**(code **)*pObj)(pObj, &GUID, &outPtr)` — the first vtable call (offset 0x00) is always QI.
- `CreateSwapChain` pattern: `(**(code **)(*factory + 0x50))(factory, device, &desc, &outSwapChain)` — DX11 legacy path.
- `CreateSwapChainForHwnd` pattern: `(**(code **)(*factory + 0x78))(factory, cmdQueueOrDevice, hwnd, &desc, pFullscreenDesc, pRestrictToOutput, &outSwapChain)` — DX11/DX12 modern path.
- After creation, the swapchain is often QI'd for a higher interface (e.g. IDXGISwapChain -> IDXGISwapChain3) and stored in an object field.

### 4. Trace from dynamic library loading (fallback)

If GUID xrefs don't lead anywhere:
1. Find xrefs to the `"dxgi.dll"` string — these are `LoadLibrary` calls.
2. Decompile those functions and look for `GetProcAddress` calls with `"CreateDXGIFactory"`.
3. Follow the factory pointer to find `CreateSwapChain` / `CreateSwapChainForHwnd` calls.
4. The swapchain output parameter reveals where it's stored.

### 5. Identify the global pointer chain

The goal is to find a **global variable** that holds (directly or via a struct) the `IDXGISwapChain*`. Typical patterns:

- **Direct global**: `g_pSwapChain` — a global `IDXGISwapChain*`.
- **Device wrapper**: A global `GfxDevice*` with swapchain at a fixed offset (e.g. `+0x320` for Unity DX11, `+0x4768 -> +0x10` for Unity DX12).

Trace the function that stores the swapchain pointer:
1. Identify which parameter or local receives the `CreateSwapChain` output.
2. Follow where it's stored (e.g. `*(param_1 + 0x320) = swapChain`).
3. Find callers to determine what `param_1` is — look for global variable reads with `MOV reg, [RIP+offset]`.

### 6. Build a scannable byte pattern

Once you've found the code that loads the global:
1. Use `read_memory` on the function to get raw bytes around the `MOV reg, [RIP+offset]` instruction that loads the global.
2. Construct a pattern:
   - Use literal bytes for opcodes and distinctive context.
   - Use `??` wildcards for the 4-byte RIP-relative offset (changes across builds).
   - Wildcard register-dependent bytes that may change (e.g. displacement fields in MOV instructions where the register choice varies).
3. Verify uniqueness with `search_byte_patterns` — must return exactly 1 match.
4. Widen the pattern if not unique, or relax wildcards if no matches.

### 7. Document the findings

Rename functions, globals, and label GUIDs in Ghidra:
- `rename_function` for key functions (creation, init, present wrappers).
- `create_label` for GUID data locations.
- `rename_data` for global pointers.
- `set_plate_comment` on key functions documenting the pointer chain and vtable offsets.

### 8. Report to user

Provide:
- The **byte pattern** in the project's `Pattern<"...">` format.
- The **PointerCalculator chain** (e.g. `ptr.Add(11).Rip()`) to resolve the pattern to the global.
- The **struct offset** to reach `IDXGISwapChain*` from the global (e.g. `+0x320`).
- The **COM vtable indexes** for hooking: Present = 8, ResizeBuffers = 13, Present1 = 22.
- A recommendation on hooking strategy:
  - **DetourHook** (recommended): Read vtable entry from live swapchain, patch function code. Works reliably across COM wrappers and proxy objects.
  - **VMT Hook**: Swap vtable pointer on the COM object. Fragile with DXGI — COM proxy/wrapper objects and multiple-interface QI can cause the hook to miss calls.

## Known engine-specific layouts

### Unity (UnityPlayer.dll)
- Rendering lives in `UnityPlayer.dll`, not `GameAssembly.dll`.
- The engine loads `dxgi.dll`, `d3d11.dll`, `d3d12.dll` dynamically via `LoadLibraryA` / `GetProcAddress`.
- Main entry point: `InitializeOrResetSwapChain` — switches on renderer type stored in the GfxDevice object.
- Renderer type values: `2` = DX11, `0x12` = DX12, `0x15` = Vulkan.
- DX11 path: `GfxDeviceDX11 + 0x320` = `IDXGISwapChain*`, `+0x328` = `IDXGISwapChain2*`.
- DX12 path: `GfxDeviceD3D12 + 0x4768` = swapchain wrapper, `wrapper + 0x10` = `IDXGISwapChain3*`.
- Look for the log string `"InitializeOrResetSwapChain %dx%d"` to confirm you've found the right function.
- Unity uses D3D11On12 interop when running DX12.

## Important notes

- **VMT hooking COM objects is unreliable** for DXGI. The DXGI runtime uses internal wrapper/proxy layers. A detour hook on the function code is strongly preferred.
- **Swapchain may not exist at injection time.** If the pattern resolves to a global pointer, verify the pointed-to object is non-null before reading the vtable. Use a polling loop if needed.
- **Always verify offsets are correct** by checking the decompiled code — struct layouts can shift between game versions.
