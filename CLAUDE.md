# LEGO Racers Decompilation

Decompilation of LEGO Racers (1999) using MSVC 6.0 (Optimizing Compiler, cl.exe 12.00.8168). Modeled after the [LEGO Island decompilation](https://github.com/isledecomp/isle).

Two targets:
- **LEGORACERS** — `LEGORacers.exe` (~3986 functions)
- **GOLDP** — `GolDP.dll` (~1071 functions)

## Building

```
<path-to-msvc6>\VC98\Bin\VCVARS32.BAT
mkdir build && cd build
cmake .. -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build .
cmake --build .
```

Portable MSVC 6.0: https://github.com/isledecomp/MSVC600-8168

Double `cmake --build` is needed due to an NMake bug. Both binaries link against `MSVCRT.dll` (dynamic CRT, `/MD`).

## reccmp

```bash
pip install -r tools/requirements.txt

# Compare (run from build/ directory)
reccmp-reccmp --target LEGORACERS --print-rec-addr
reccmp-reccmp --target GOLDP --verbose 0x100070b0 --print-rec-addr

# Progress SVGs
reccmp-reccmp --target LEGORACERS --total 3986 --nolib -S LEGORACERSPROGRESS.SVG --svg-icon assets/legoracers.png
reccmp-reccmp --target GOLDP --total 1071 --nolib -S GOLDPPROGRESS.SVG --svg-icon assets/goldp.png

# Lint annotations
reccmp-decomplint LEGORACERS --module LEGORACERS --warnfail
reccmp-decomplint GOLDP --module GOLDP --warnfail
```

`reccmp-user.yml` (gitignored) points to original binaries for local comparison.

## Annotations

Functions in a compilation unit must be ordered by address (ascending).

```cpp
// FUNCTION: LEGORACERS 0x449d50    — complete, compared by reccmp
// STUB: GOLDP 0x10006ff0           — incomplete, skipped by reccmp
// LIBRARY: GOLDP 0x1004b356        — CRT/3rd-party (in library_msvc.h, inside #ifdef 0)
// SYNTHETIC: GOLDP 0x10007040      — compiler-generated (scalar deleting destructors)
// GLOBAL: LEGORACERS 0x4c47e4      — global variable
// VTABLE: GOLDP 0x10056440         — virtual function table
// SIZE 0xc8ac8                      — struct/class size assertion
```

## Class Pattern

```cpp
// header:
// VTABLE: GOLDP 0x10056440
// SIZE 0xc8ac8
class VelvetThunder821960 : public PixelDust4 {
public:
    virtual ~VelvetThunder821960();    // vtable+0x00
    virtual void VTable0x04();         // vtable+0x04

    // SYNTHETIC: GOLDP 0x10007040
    // VelvetThunder821960::`scalar deleting destructor'

private:
    int m_unk0x04;               // 0x04
    float m_unk0x08;             // 0x08
    undefined m_unk0x0c[0x100];  // 0x0c
};

// source:
DECOMP_SIZE_ASSERT(VelvetThunder821960, 0xc8ac8)
```

Member offset comments (`// 0xNN`) and vtable offset comments (`// vtable+0xNN`) are required.

## Naming Conventions

Uses LEGO Island NCC rules (`tools/ncc/ncc.style`), enforced in CI:
- Functions: `FUN_XXXXXXXX` (8 hex digits, lowercase)
- Globals: `g_unk0xXXXXXXXX`
- Members: `m_unk0xXX` (by offset)
- Parameters: `p_unk0xXX`
- Unknown classes: `RandomNameSize` (random PascalCase name + decimal size suffix, e.g. `NeonCactus7532`, `VelvetThunder821960`)
- Virtual methods: `VTable0xXX` (by vtable offset)
- Enum constants: `c_` prefix
- All parameters: `p_` prefix, all members: `m_` prefix, all globals: `g_` prefix
- Variable names should match across prefixes when assigned: `m_hInstance = p_hInstance`, never `m_hInstance = p_something`

## Types

Use Lego types from `util/types.h` (`#include "types.h"`) instead of primitive C types:
- `LegoS8`, `LegoU8` instead of `char`, `unsigned char`
- `LegoS16`, `LegoU16` instead of `short`, `unsigned short`
- `LegoS32`, `LegoU32` instead of `int`, `unsigned int`
- `LegoFloat` instead of `float`
- `LegoChar` instead of `char` (for character data)
- `LegoBool` for booleans

When a variable's type is dictated by an external interface (Windows API return types, parameters of WinMain/DllMain, etc.), keep the original type — do not replace with Lego types. Lego types are for game code, not API boundaries.

## Decompiling a New Function

1. **Find the decompilation** for the target address. Read the function body and note all called functions and global references.

2. **Check calling conventions** carefully. Per-call-site guessed types may differ from the actual function definition. Cross-reference: find the called function's own definition to confirm `__thiscall` vs `__cdecl` vs `__stdcall`. If a function is `__thiscall`, it is a class member — look for the object it operates on.

3. **Identify classes from `__thiscall` patterns.** When a function is called with a global address and `__thiscall` convention, that global is a class instance. Create a class with `undefined m_unk0x00[size]` for unknown internals.

4. **Create STUBs for all unknown called functions.** Every function your implementation calls must exist (even as a stub) for the build to succeed and reccmp to compare. Order stubs by address ascending within each file.

5. **Watch for COMDAT folding.** MSVC 6.0's linker may merge identical stub functions (e.g. two empty `void` methods), causing reccmp to report a mismatch on the call target. Fix by giving stubs different signatures or return types.

6. **Write clean C++, not pseudocode.** Translate raw pointer arithmetic (`*(_DWORD*)(this + 4)`) into proper member access, method calls, and named variables. Refer to existing `// FUNCTION:` implementations (not STUBs) in the codebase for the expected style.

7. **Build with double `cmake --build`**, then compare: `reccmp-reccmp --target LEGORACERS --verbose 0xADDRESS --print-rec-addr`. Iterate until 100%.

## Project Structure

```
LEGORacers/          # LEGORacers.exe source
GolDP/               # GolDP.dll source
  include/           # Headers
  src/               # Source files
  GolDP.def          # DLL exports (GolEntry, GolExit)
  library_msvc.h     # CRT library annotations
util/                # decomp.h, compat.h, types.h
cmake/               # reccmp CMake integration
data/                # Original binaries and decompilation data (gitignored)
```
