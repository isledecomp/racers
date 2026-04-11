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

# Lint annotations (pass source dir to avoid scanning gitignored files)
reccmp-decomplint --module LEGORACERS --warnfail <path-to-LEGORacers>
reccmp-decomplint --module GOLDP --warnfail <path-to-GolDP>
```

`reccmp-user.yml` (gitignored) points to original binaries for local comparison.

## Annotations

Functions in a compilation unit must be ordered by address (ascending).

```cpp
// FUNCTION: LEGORACERS 0x449d50    — complete, compared by reccmp
// FUNCTION: LEGORACERS 0x4164c0 FOLDED — identical code merged by linker (see below)
// STUB: GOLDP 0x10006ff0           — incomplete, skipped by reccmp
// LIBRARY: GOLDP 0x1004b356        — CRT/3rd-party (in library_msvc.h, inside #ifdef 0)
// SYNTHETIC: GOLDP 0x10007040      — compiler-generated (scalar deleting destructors)
// GLOBAL: LEGORACERS 0x4c47e4      — global variable
// VTABLE: GOLDP 0x10056440         — virtual function table
// SIZE 0xc8ac8                      — struct/class size assertion
```

**FOLDED functions:** MSVC 6.0's linker merges functions with identical compiled code (Identical COMDAT Folding). Multiple distinct functions end up sharing one address in the original binary. Annotate each with `// FUNCTION: MODULE 0xADDRESS FOLDED` where the address is the single copy the linker kept. All folded functions share the same address. Functions that fold together have the same signature and body (e.g. all empty `void` methods fold to one address, all empty `void(undefined4)` methods fold to a different address). FOLDED functions are exempt from the address-ascending ordering rule and do not need the `STUB()` anti-folding macro.

## Class Pattern

```cpp
// header:
// VTABLE: GOLDP 0x10056440
// SIZE 0xc8ac8
class VelvetThunder0xc8ac8 : public PixelDust0x4 {
public:
    virtual ~VelvetThunder0xc8ac8();    // vtable+0x00
    virtual void VTable0x04();          // vtable+0x04

    // SYNTHETIC: GOLDP 0x10007040
    // VelvetThunder0xc8ac8::`scalar deleting destructor'

private:
    int m_unk0x04;               // 0x04
    float m_unk0x08;             // 0x08
    undefined m_unk0x0c[0x100];  // 0x0c
};

// source:
DECOMP_SIZE_ASSERT(VelvetThunder0xc8ac8, 0xc8ac8)
```

Member offset comments (`// 0xNN`) and vtable offset comments (`// vtable+0xNN`) are required.

**Overrides:** When a derived class overrides a virtual method from a base class, use `override` instead of `virtual` (e.g. `void VTable0x04() override;`). Include `compat.h` which defines `override` as empty for MSVC 6.0 compatibility.

## Naming Conventions

Uses LEGO Island NCC rules (`tools/ncc/ncc.style`), enforced in CI:
- Functions: `FUN_XXXXXXXX` (8 hex digits, lowercase)
- Globals: `g_unk0xXXXXXXXX`
- Members: `m_unk0xXX` (by offset)
- Parameters: `p_unk0xXX`
- Unknown classes: `RandomName0xSize` (random PascalCase name + `0x` + hex size suffix, e.g. `NeonCactus0x1d6c`, `VelvetThunder0xc8ac8`)
- Virtual methods: `VTable0xXX` (by vtable offset)
- Enum constants: `c_` prefix
- All parameters: `p_` prefix, all members: `m_` prefix, all globals: `g_` prefix
- Variable names should match across prefixes when assigned: `m_hInstance = p_hInstance`, never `m_hInstance = p_something`
- **Unused parameters** must be unnamed (omit the parameter name in the definition)

## Types

Use Lego types from `util/types.h` (`#include "types.h"`) instead of primitive C types:
- `LegoS8`, `LegoU8` instead of `char`, `unsigned char`
- `LegoS16`, `LegoU16` instead of `short`, `unsigned short`
- `LegoS32`, `LegoU32` instead of `int`, `unsigned int`
- `LegoFloat` instead of `float`
- `LegoChar` instead of `char` (for character data)
- `LegoBool` for booleans

When a variable's type is dictated by an external interface (Windows API return types, parameters of WinMain/DllMain, etc.), keep the original type — do not replace with Lego types. Lego types are for game code, not API boundaries.

**Unknown/unproven types:** When a variable's type has not been confirmed, use `undefined` types (`undefined`, `undefined2`, `undefined4` from `decomp.h`). Use `undefined4*` for pointers to unknown data. Do not guess concrete types (e.g. `int`, `float`, `void*`) until the type is proven by usage context or reccmp comparison.

## Decompiling a New Function

1. **Find the decompilation** for the target address. Read the function body and note all called functions and global references.

2. **Check calling conventions** carefully. Per-call-site guessed types may differ from the actual function definition. Cross-reference: find the called function's own definition to confirm `__thiscall` vs `__cdecl` vs `__stdcall`. If a function is `__thiscall`, it is a class member — look for the object it operates on.

3. **Identify classes from `__thiscall` patterns.** When a function is called with a global address and `__thiscall` convention, that global is a class instance. Create a class with `undefined m_unk0x00[size]` for unknown internals.

4. **Create STUBs for all unknown called functions.** Every function your implementation calls must exist (even as a stub) for the build to succeed and reccmp to compare. Order stubs by address ascending within each file.

5. **Watch for COMDAT folding.** MSVC 6.0's linker may merge identical stub functions (e.g. two empty `void` methods), causing reccmp to report a mismatch on the call target. Use the `STUB(0xADDRESS)` macro (from `decomp.h`) in every stub body — it assigns a unique value to `g_foldingDummyVariable`, giving each stub a distinct body so the linker won't fold them. Use the function's real address as the value. Empty destructors are an exception: they have distinct compiler-generated code and don't need the macro.

6. **Write clean C++, not pseudocode.** Translate raw pointer arithmetic (`*(_DWORD*)(this + 4)`) into proper member access, method calls, and named variables. Refer to existing `// FUNCTION:` implementations (not STUBs) in the codebase for the expected style.

7. **Build with double `cmake --build`**, then compare: `reccmp-reccmp --target LEGORACERS --verbose 0xADDRESS --print-rec-addr`. Iterate until 100%.

8. **Validate vtables.** After adding or modifying virtual methods, always verify the vtable matches: `reccmp-reccmp --target LEGORACERS --verbose 0xVTABLE_ADDR --print-rec-addr`. Every virtual method declared in a class header must have a corresponding `// STUB:` annotation with its real address from the original binary. Read the vtable data from the original binary to find the function address at each vtable slot.

9. **Check for regressions.** After any change, re-verify all previously matched `// FUNCTION:` implementations that touch the same classes, especially functions that make virtual calls on modified classes.

10. **Lint annotations.** Run `reccmp-decomplint` from the `build/` directory (see example commands in the reccmp section above). Always pass the source directory as a path argument to avoid scanning gitignored data files.

## Decompilation Principles

- **Every type must be corroborated by matched code.** Do not assign concrete member types based solely on IDA/Ghidra analysis. A type is only proven when a `// FUNCTION:` annotation using that type achieves 100% reccmp match. Until then, use `undefined`/`undefined4`.
- **Vtable set position proves class hierarchy.** In MSVC 6.0, the vtable is set at the start of the constructor body, after all base constructors. If the vtable set appears AFTER some member initialization, that initialization belongs to a base class constructor (possibly inlined). Use this to determine inheritance structure.
- **Multiple inheritance is real.** When a C-style cast compiles to a pointer subtraction, it's a cross-cast from a second base class. Define proper inheritance so the compiler generates the adjustment — never use raw pointer arithmetic to fake it.
- **No raw pointer arithmetic as a substitute for types.** If you find yourself writing pointer casts and subtractions, the types are wrong. Find the actual class type so the cast is a legitimate C++ conversion.
- **Read the original binary directly** (via Python/struct) to determine vtable entries, call targets, and function addresses when IDA/Ghidra mislabels or hides them.
- **Every annotation must have the real address.** No placeholders, no guesses. Read the vtable data or compute call targets from the binary to get exact addresses.
- **Functions marked `// FUNCTION:` must be 100% match.** If reccmp shows any diff, the code is wrong — do not accept partial matches or mark as FUNCTION. Investigate the diff to find the root cause (wrong class layout, wrong types, missing base class, etc.).
- **Validate with `reccmp-vtable`** in addition to `reccmp-reccmp`. Vtable mismatches reveal missing/wrong virtual method declarations even when individual functions appear correct.
- **Inline base constructors affect layout.** If a base class constructor is small enough, MSVC 6.0 inlines it. The inlined code appears between the outer base constructor call and the derived vtable set. Recognize this pattern to identify intermediate base classes.

## Project Structure

```
LEGORacers/          # LEGORacers.exe source
  include/           # Headers
  src/               # Source files
GolDP/               # GolDP.dll source
  include/           # Headers
  src/               # Source files
  GolDP.def          # DLL exports (GolEntry, GolExit)
  library_msvc.h     # CRT library annotations
util/                # decomp.h, compat.h, types.h
cmake/               # reccmp CMake integration
data/                # Original binaries and decompilation data (gitignored)
```
