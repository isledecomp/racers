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

# Compare global variable data values
reccmp-datacmp --target LEGORACERS --verbose --print-rec-addr
reccmp-datacmp --target GOLDP --verbose --print-rec-addr

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
// FUNCTION: LEGORACERS 0x00449d50    — complete, compared by reccmp
// FUNCTION: LEGORACERS 0x004164c0 FOLDED — identical code merged by linker (see below)
// STUB: GOLDP 0x10006ff0             — incomplete, skipped by reccmp
// LIBRARY: GOLDP 0x1004b356          — CRT/3rd-party (in library_msvc.h, inside #ifdef 0)
// SYNTHETIC: GOLDP 0x10007040        — compiler-generated (scalar deleting destructors)
// GLOBAL: LEGORACERS 0x004c47e4      — global variable
// VTABLE: GOLDP 0x10056440           — virtual function table
// SIZE 0xc8ac8                        — struct/class size assertion
```

**GLOBAL variables** have a pointer address and may point to initialized data. A `// GLOBAL:` annotation marks the address of the pointer variable itself. If the variable is a `char*` pointing to a string literal, the address of where the string data lives should be in `reccmp/lego-racers-ascii.csv`

```cpp
// GLOBAL: LEGORACERS 0x004be8d8      — address of the pointer variable
LegoChar* g_jamFile = "lego.jam";
```

When adding or modifying globals, always run `reccmp-datacmp` to verify the initial values match the original binary. Global variables with non-zero initial values (strings, pointers, constants) must be initialized to match.

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

**Gap members:** When declaring `undefined` arrays to fill gaps between typed members, use a subtraction expression rather than a hardcoded size. This makes the size self-documenting and avoids manual recalculation when members are added:

```cpp
undefined m_unk0x05[0x7dc - 0x05];   // 0x05  (gap until next member at 0x7dc)
undefined m_unk0x92c[0x944 - 0x92c]; // 0x92c (gap until end of class at 0x944)
```

**Overrides:** When a derived class overrides a virtual method from a base class, use `override` instead of `virtual` (e.g. `void VTable0x04() override;`). Include `compat.h` which defines `override` as empty for MSVC 6.0 compatibility.

## Code Style

**Bit tests:** Use concise style without explicit comparison to zero:
- `if (flags & c_flagCached)` — not `if ((flags & c_flagCached) != 0)`
- `if (!(flags & c_flagCached))` — not `if ((flags & c_flagCached) == 0)`

**Address padding:** All annotation addresses (not sizes) must be zero-padded to 8 hex digits: `0x00449d50`, not `0x449d50`.

**Annotation ordering:** When a function or entity has annotations for both GOLDP and LEGORACERS, the GOLDP annotation must come first.

**Win32 API: prefer un-suffixed names.** Use `ChangeDisplaySettings`, `MessageBox`, `RegisterClass`, `CreateWindowEx`, `LoadIcon`, `DEVMODE`, `MSG`, etc. — NOT the explicit `A`/`W` variants like `ChangeDisplaySettingsA`, `MessageBoxA`, `DEVMODEA`. The un-suffixed names are macros from `<windows.h>` that resolve to the `A` form when `UNICODE` is undefined (the project default), so the compiled binary still imports `ChangeDisplaySettingsA` and uses the `DEVMODEA` struct. The original game source used the macros; matching that style keeps the source readable and consistent. This applies to both **functions** (`CreateWindow`, `SetWindowText`) and **types** (`DEVMODE`, `WIN32_FIND_DATA`, `LOGFONT`). IDA pseudocode shows the resolved `*A` symbol — translate it back to the macro when transcribing.

**No redundant `this->`.** Inside a member function, write `m_member`, `Method()`, and `BaseClass::VirtualMethod()` directly — don't prefix with `this->`. The implicit `this` is enough. The one place you might *think* you need it — calling a base-class virtual non-virtually (`this->Base::Foo()`) — also doesn't need the prefix; `Base::Foo()` from inside a derived member compiles to the same direct call.

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

When a variable's type is dictated by an external interface (Windows API, DirectX, CRT, etc.), keep the original type — do not replace with Lego types. Lego types are for game code, not API boundaries. `void*` can remain.

**Unknown/unproven types:** When a variable's type has not been confirmed, use `undefined` types (`undefined`, `undefined2`, `undefined4` from `decomp.h`). Use `undefined4*` for pointers to unknown data. Do not guess concrete types (e.g. `int`, `float`, `void*`) until the type is proven by usage context or reccmp comparison.

## Decompiling a New Function

1. **Find the decompilation** for the target address. Read the function body and note all called functions and global references.

2. **Check calling conventions** carefully. Per-call-site guessed types may differ from the actual function definition. Cross-reference: find the called function's own definition to confirm `__thiscall` vs `__cdecl` vs `__stdcall`. If a function is `__thiscall`, it is a class member — look for the object it operates on.

3. **Identify classes from `__thiscall` patterns.** When a function is called with a global address and `__thiscall` convention, that global is a class instance. Create a class with `undefined m_unk0x00[size]` for unknown internals.

4. **Create STUBs for all unknown called functions.** Every function your implementation calls must exist (even as a stub) for the build to succeed and reccmp to compare. Order stubs by address ascending within each file.

5. **Watch for COMDAT folding.** MSVC 6.0's linker may merge identical stub functions (e.g. two empty `void` methods), causing reccmp to report a mismatch on the call target. Use the `STUB(0xADDRESS)` macro (from `decomp.h`) in every stub body — it assigns a unique value to `g_foldingDummyVariable`, giving each stub a distinct body so the linker won't fold them. Use the function's real address as the value. Empty destructors are an exception: they have distinct compiler-generated code and don't need the macro.

6. **Write clean C++, not pseudocode.** Translate raw pointer arithmetic (`*(_DWORD*)(this + 4)`) into proper member access, method calls, and named variables. Refer to existing `// FUNCTION:` implementations (not STUBs) in the codebase for the expected style.

7. **Build with double `cmake --build`**, then compare: `reccmp-reccmp --target LEGORACERS --verbose 0xADDRESS --print-rec-addr`. Iterate until 100%.

7b. **Verify global data** with `reccmp-datacmp --target LEGORACERS --verbose --print-rec-addr`. Any `// GLOBAL:` variable with non-zero initial data must match the original binary. This catches uninitialized globals that should have string pointers, default values, etc.

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

## Prioritize Constructors, Destructors, and Scalar Deleting Destructors

When decompiling a new class, focus on matching its **constructor**, **destructor**, and **scalar deleting destructor** first. These functions directly verify the class layout:
- Constructors reveal member initialization order, base class chain (via vtable sets), and member types.
- Destructors reveal cleanup order and virtual method calls, confirming the vtable layout.
- Scalar deleting destructors are compiler-generated and verify the class size and destructor linkage.

Matching these three functions provides high confidence that the class header (size, inheritance, vtable, members) is correct before attempting more complex methods.

## MSVC 6.0 Codegen Patterns

- **Return types affect register allocation.** Changing a function from `void` to returning a pointer/int can significantly change which registers the compiler assigns to local variables and parameters. If register allocation doesn't match, check whether the original function returns a value (IDA's guessed return type is a hint).
- **Float literal assignments may compile to integer `mov`.** MSVC 6.0 with `/O2` optimizes `float_member = 1.0f` to `mov dword ptr [offset], 0x3F800000` (an integer immediate store) rather than `fld`/`fstp`. Using `LegoFloat` members with float literals still produces the correct integer stores.
- **Inline getters/setters produce matching code for cross-object member access.** When a function accesses internal members of a composed sub-object (e.g. `NeonCactus` accessing `IronFlame`'s private members), use public inline getters/setters on the sub-object class. MSVC 6.0 with `/O2` inlines these, producing identical code to direct member access — and can even improve register scheduling to match the original binary more closely than making members public.
- **Inline functions can change register allocation.** When register allocation doesn't match, try replacing inline getter/setter calls (e.g. `SetFlags(GetFlags() | flag)`) with direct member access (e.g. `m_flags |= flag`). Inline function expansion changes the compiler's intermediate representation and can cause it to assign callee-saved registers (esi, edi, ebp) differently. This applies to all trivial inlines — flag accessors, dimension getters, name getters, etc. Always try both patterns (inline vs direct) when debugging register allocation mismatches.
- **Loop-back pattern identifies the C++ loop form.** When the original assembly ends a loop with `test <reg>, <reg>; jne <loop_top>` where `<reg>` holds a pointer updated inside the loop, the source was almost certainly `while (ptr) { ... }` or `do { ... } while (ptr);` with that pointer as the condition — not `for (;;)` + break. `for (;;)` with breaks typically produces a different loop-back (another explicit condition test or `jmp` to loop top). IDA's `while (v6 != (char *)-1)` decompilation of this pattern is misleading; the actual assembly tests `!= 0`, so the source condition is `while (ptr)`.
- **Loop condition variables get register priority.** MSVC 6.0 /O2 tends to allocate the `while`/`do-while` condition variable to the first callee-saved register (ebx), pushing other hot variables like `this` to later registers (ebp). Using `for (;;)` with breaks instead lets `this` take ebx. If register allocation swaps but the behavior is identical, reccmp reports "100% effective match" — this is a complete match for decompilation purposes (no code change would make the bytes identical without changing register allocation in a way that affects other functions).
- **Use `sizeOfArray(m_member)` for array-size loop bounds.** When iterating a class member array, prefer `sizeOfArray(m_files)` over the hard-coded count (e.g. `20`). `sizeOfArray` is compile-time evaluated to the same immediate, so codegen is identical, but the source is self-documenting and robust to array resizes.
- **Write human-readable code, not IDA pseudocode.** The decompiled code should look like it was written by a human programmer. Avoid `goto` patterns, raw integer bit patterns for floats, and other artifacts of decompilation. Use proper types, named variables, and clean control flow. Iterate with reccmp to ensure the clean version still matches.
- **Decomposing `if/else if` from asm.** A redundant-looking second conditional jump whose flags come from a much earlier `cmp` — e.g. `cmp ebp, 0xc ; jae label ; ... ; label: jne skip ; body ; skip:` — reveals an `else if` chain in the source. The correct form is usually `if (x < N) { main } else if (x == N) { body }`, NOT the reversed `if (x >= N) { body } else { main }` that IDA often shows. The `else if` branch body ends up physically at the end of the enclosing block, reached by a forward jump from the outer test. This restructuring often also unlocks different register allocation (e.g. pointer-walk vs index-form loops), because it changes how the compiler accounts for uses of the loop counter.
- **Byte-loop hash accumulator pattern.** For a hash loop reading bytes from a string, prefer loading the byte into a local (`LegoChar c = p_str[i];`) and folding the shift directly into the accumulator (`acc += c << shift;`) rather than extracting a separate temp (`int v = p_str[i] << shift; acc += v;`). The temp pattern changes register allocation — the accumulator lands in a caller-saved register (`eax`) instead of callee-saved (`esi`) — which cascades to `this`/`p_str` register choices and stack-frame size.
- **Loop-index variable scoping.** Declare `LegoU32 i;` before the first `for` loop, not inside the init. MSVC 6.0's legacy for-scoping lets `i` leak into the enclosing block (so a second `for (i = ...)` reusing the same variable compiles), but CI runs clang-tidy under modern ANSI scoping where the second loop sees `i` as undeclared. The compatible form is `LegoU32 i;` at function scope + `for (i = 0; ...; i++) { ... }`.
- **`mov ecx, X; call F` indicates `__thiscall`** — even when `F`'s body never reads `this`. The `mov ecx` only makes sense if the call expects `this` in `ecx`. Source-side, declare `F` as a non-static member of the class whose pointer is in `ecx`; the body can ignore `this` (e.g. a wrapper around a Win32 call). Declaring it as a free function would emit just `call F` without the preceding `mov ecx`, and the caller's match would break. Conversely, if there's NO `mov ecx, X` before `call F`, F is NOT `__thiscall` (it's `__cdecl`/`__stdcall`/static).
- **Direct call to a folded empty method = explicit base-scope call.** A direct `call <addr>` (opcode `e8`) where `<addr>` is the COMDAT-folded landing pad for empty `void f()` thiscalls (e.g. `0x4164C0` in LEGORacers, where every empty `void Class::Method()` body lands) reproduces from a non-virtual call to a base-class virtual: `BaseClass::VTable0xNN();` inside a derived member function. The explicit `BaseClass::` qualifier suppresses virtual dispatch and emits a direct call; the linker resolves it to the folded address. A virtual call (`this->VTable0xNN()` or just `VTable0xNN()` on a virtual method) would instead emit `mov eax, [ecx]; call dword ptr [eax+N]` — completely different bytes. Use this pattern when you see a stray `call <folded_empty_addr>` that isn't accounted for by any non-virtual member.
- **`else if (!cond)` inverts code block layout.** When the binary places the body of a conditional branch physically AFTER the function's `ret` (reached via forward jump, with a `jmp` back to the main flow), MSVC 6.0 has treated the branch as cold. To reproduce, invert the condition and use `else if`: `if (!X) { hot_body; } else if (cond) { cold_body; continue; }` — the cold body lands at the end of the function. Writing the natural `if (X) { cold_body } else { hot_body }` produces inline layout instead and won't match.
- **MSVC 6.0 does NOT tail-call `__cdecl` functions.** A trivial forwarding wrapper `int Outer(a,b,c,d) { return Inner(a,b,c,d); }` does not compile to `jmp Inner` for `__cdecl` callees — MSVC emits a ~30-byte "re-push and call" prologue/call/epilogue instead. Two separate functions end up in the binary. Only `__thiscall` allows tail-call (`~Class() { Release(); }` → 5-byte `jmp Release`). When the binary shows this double-dispatch pattern between `__cdecl` functions, plan for a real wrapper + impl in source.
- **Caller-side inline getters fix register allocation across objects.** When a function accesses members of a passed-in object pointer, replacing direct field access with a public inline getter on the target class changes the register allocator's treatment of the read, even though the compiled body is identical. Promote `ptr->m_foo` to `ptr->GetFoo()` and add `Type GetFoo() { return m_foo; }` to the target class header. MSVC 6.0 /O2 inlines it, and register scheduling often shifts to match the original. Applies especially when the cross-object member access involves a write-then-call sequence where the compiler's pre-call register scheduling matters.
- **Function overloads via `int` vs typedef'd unsigned int.** `int` (signed) and a typedef like `LegoBool32`/`LegoU32` (unsigned int) are distinct types under C++ overload resolution despite identical storage. Useful when the binary has a tiny `__cdecl` wrapper that forwards to a same-signature implementation: declare the wrapper with `(int, int)` and the impl with `(LegoBool32, LegoBool32)` under the same name. The wrapper casts (`return Name(..., (LegoBool32)c, (LegoBool32)d);`) to force the overload — without casts, overload resolution picks the exact-match signature (itself) and recurses infinitely.

## COMDAT Folding Across Targets

A function in `common/src/` that is compiled into both `legoracers.exe` and `goldp.dll` can need different COMDAT fold groups in each target — e.g. a trivial `return 0;` function that folds with a group of empty STUBs in one target but stays independent in the other.

To achieve a different fold behavior per target, wrap the `STUB(0xADDRESS)` macro in `#ifdef BUILDING_GOL` and annotate both targets:

```cpp
// FUNCTION: GOLDP 0xAAAAAAAA FOLDED
// FUNCTION: LEGORACERS 0xBBBBBBBB
LegoS32 Class::Method()
{
#ifdef BUILDING_GOL
    STUB(0xAAAAAAAA);
#endif
    return c_successCode;
}
```

In GOLDP the `STUB(...)` write to `g_foldingDummyVariable` makes the body identical to other `STUB(0xAAAAAAAA)` stubs and they fold together; in LEGORACERS the macro is gone and the function compiles to the standalone `xor eax, eax; ret` that LEGORACERS matches at its own address.

## Vtable annotation syntax

Class-header annotations require the colon: `// VTABLE: MODULE 0xADDRESS`, not `// VTABLE MODULE 0xADDRESS`. reccmp silently ignores the colonless form, and vtable set sites inside destructors/constructors then show up in the diff as `<OFFSET2>` instead of the resolved `ClassName::vftable`, costing the 5–10% match. Same rule for `// FUNCTION:`, `// STUB:`, `// GLOBAL:`, `// SYNTHETIC:`, `// SIZE` (size is an exception — no colon, per the existing convention).

## Scalar Deleting Destructor Inlining

For small classes, MSVC 6.0 inlines the destructor body directly into the compiler-synthesized *scalar deleting destructor* (SDD) rather than calling the destructor. If the SDD is <40% match while the destructor itself is 100%, the asm likely shows the destructor body inlined (e.g. setting the vftable, deleting a member, clearing a field) immediately followed by the standard `test byte [esp+N], 1 / je / delete this / ret 4` tail — whereas your build emits a plain `call Class::~Class` before that tail.

To get the SDD to inline, move the destructor body into the class declaration in the header (implicit inline):

```cpp
class Small {
public:
    // FUNCTION: MODULE 0xADDR  (keep the annotation on the inline definition)
    virtual ~Small()
    {
        if (m_data != NULL) {
            delete[] m_data;
            m_data = NULL;
        }
    }
};
```

This pushes every translation unit that includes the header toward inlining the destructor, which is exactly what you want inside the SDD. But it also causes *inlining at unwanted call sites* — notably, a containing class's destructor that must emit 5 distinct calls to `~Small()` for five `Small` members will inline the body five times instead, breaking that containing destructor's match.

Guard against that with `#pragma inline_depth(0)` around the containing destructor definition:

```cpp
// TODO: Temporary workaround until we figure out how the original code was written.
#pragma inline_depth(0)
OuterClass::~OuterClass()
{
    // compiler-emitted member destructor calls stay as calls
}
#pragma inline_depth()
```

This keeps the SDD's inlined-destructor match AND the outer destructor's call-based match. The pragma only affects the single function definition it wraps.

**`#pragma inline_depth(0)` is a temporary workaround.** It is not how the original developers wrote their code — they got matching codegen without the pragma. Every use of this pragma carries a standard TODO comment:

```cpp
// TODO: Temporary workaround until we figure out how the original code was written.
```

The original likely used some combination of source-level choices (inline vs. out-of-line definition placement, header layout, compiler flags, build-time codegen settings) that biased MSVC 6.0's inliner the right way without needing a pragma. Prefer discovering that configuration over propagating the pragma. When you add a new `#pragma inline_depth(0)`, include the TODO comment verbatim so it's easy to grep for and revisit.

## Per-target Inline Definition Placement

A common-layer function (in `common/src/`) can need different inlining decisions between the LEGORACERS and GOLDP targets — e.g. a small `Init()` helper that the compiler inlines into all callers in one target but calls as a function in the other. If the asm shows the helper *expanded* inside caller A and *called* from caller B, split the definition by target:

```cpp
// header
class Class {
#ifdef BUILDING_GOL
    // FUNCTION: GOLDP 0xADDR
    virtual ~Class()
    {
        // body, inlined by every TU that compiles for GOLDP — so the GOLDP SDD
        // and anything else that wants the inlined form picks it up.
    }
#else
    virtual ~Class();
#endif
};
```

```cpp
// .cpp
#ifndef BUILDING_GOL
// FUNCTION: LEGORACERS 0xADDR
Class::~Class()
{
    // same body, but out-of-line in LEGORACERS — so LEGORACERS call sites
    // (constructor, SDD, other destructors) emit a real `call` and match.
}
#endif
```

The function body is duplicated, which is the downside; both copies must stay in sync. In return you get per-target inline control without any pragmas. Apply the same pattern to any helper (not just destructors) when the targets disagree on inlining.

## Naming Members from Matched Code

A member name is proven as soon as a matched function uses that member in a way that forces a specific semantic interpretation — e.g., a member that is both the subject of `count++` inside a loop bounded at 20 AND later stored into a global `g_fileSourceCount` is unambiguously a "file source count", even without external evidence. Rename `m_unk0xNN` gap placeholders to their proven semantic names once a `// FUNCTION:` match corroborates the usage. Member types still follow the `undefined`/`undefined4` rule until proven.

## Naming Functions from Matched Code

When the functionality of a matched function is clearly obvious from the implementation, rename it from `VTable0xNN` / `FUN_XXXXXXXX` to its semantic name. Evidence threshold:

- **Clear pair with a named counterpart.** e.g. `VTable0x20` calls `m_input.Shutdown()`; `VTable0x1c` at the adjacent slot calls the input-system init helper with `hInstance`/`hWnd` → `VTable0x1c` is `InitInput`.
- **Symmetric with an already-named method.** e.g. `VTable0x10` undoes every action taken by the matched `Init()` (destroys the window, closes every file source, unloads the graphics library, clears the init flag) and is also the body of `~Class()` → `Destroy`.
- **Function body leaves no interpretation.** e.g. a one-line tail call to a helper named `InitInput`, or a loop that opens every line of a newline-separated list and publishes them as globals, strongly suggests a specific name.

Do **not** rename on weak evidence. If multiple plausible names exist with no way to choose (e.g. `OpenFileSources` vs. `LoadFileSources` vs. `RegisterFileSources`), keep the placeholder `FUN_XXXXXXXX` and wait for a caller, a nearby string literal, or a symmetric counterpart to break the tie. A misleading semantic name is worse than a neutral placeholder.

Renaming a virtual method does not affect codegen — the vtable is slot-indexed by the compiler regardless of method name — so renaming is safe as long as all call sites and overrides are updated together. Verify the match still holds after the rename.

**Lifecycle method conventions across classes.** The codebase uses a consistent set of method names for object lifecycle steps. Match these when naming new methods so all classes use the same vocabulary:

- `Init()` — explicit initialization (separate from the constructor; the ctor zeroes fields, `Init` allocates resources/loads files/registers callbacks).
- `Run()` — the main loop / per-instance driver (used on the top-level app/game class).
- `Shutdown()` — release live resources (close handles, stop sound, free buffers) but leave the object reusable. Subsystem classes (`SoundManager`, `CobaltMist0x30`, `OpalVault0xf0`, `IndigoStar0x18`, `GolHashTable`) all use this name.
- `Destroy()` — full teardown: invokes `Shutdown` (and any other cleanup), then releases anything `Shutdown` left, leaving the object in its post-construction state.
- `Reset()` — return the object to a pristine zero-state (used inside constructors and destructors as a shared body, e.g. `CrimsonForge0x800::Reset`).

When you find a method that wraps subsystem teardown in a class that also has a "full destroy" wrapper, the small one is `Shutdown` and the bigger one is `Destroy` — even if it means renaming a previously-named `Shutdown` to `Destroy` to free up the name. Don't invent new terms (`Cleanup`, `Teardown`, `StopServices`) when one of the established names fits — consistency across classes is more valuable than naming creativity.

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
