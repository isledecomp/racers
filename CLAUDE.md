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
class Unk0x10056440 : public Unk0x100564b0 {
public:
    virtual ~Unk0x10056440();    // vtable+0x00
    virtual void VTable0x04();   // vtable+0x04

    // SYNTHETIC: GOLDP 0x10007040
    // Unk0x10056440::`scalar deleting destructor'

private:
    int m_unk0x04;               // 0x04
    float m_unk0x08;             // 0x08
    undefined m_unk0x0c[0x100];  // 0x0c
};

// source:
DECOMP_SIZE_ASSERT(Unk0x10056440, 0xc8ac8)
```

Member offset comments (`// 0xNN`) and vtable offset comments (`// vtable+0xNN`) are required.

## Naming Conventions

Same as LEGO Island (NCC):
- Functions: `FUN_XXXXXXXX` (8 hex digits, lowercase)
- Globals: `g_unk0xXXXXXXXX`
- Members: `m_unk0xXX` (by offset)
- Parameters: `p_unk0xXX`
- Classes: `Unk0xXXXXXXXX` (by vtable address)
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
data/                # IDA dumps (gitignored)
```
