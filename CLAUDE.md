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

Portable MSVC 6.0: https://github.com/isledecomp/MSVC600-8168. Double `cmake --build` works around an NMake bug. Both binaries link against `MSVCRT.dll` (dynamic CRT, `/MD`).

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

A `// GLOBAL:` marks the address of the pointer variable itself. If the variable is a `char*` to a string literal, the data address belongs in `reccmp/lego-racers-ascii.csv`:

```cpp
// GLOBAL: LEGORACERS 0x004be8d8
LegoChar* g_jamFile = "lego.jam";
```

Run `reccmp-datacmp` after adding/modifying globals with non-zero initial values to verify they match.

**FOLDED functions.** MSVC 6.0's Identical COMDAT Folding merges functions with identical compiled code; multiple source functions end up at one address. Annotate each with `// FUNCTION: MODULE 0xADDRESS FOLDED` (same address for all folded siblings, same signature and body — e.g. all empty `void` methods fold together). FOLDED is exempt from address-ascending order and does not need the `STUB()` anti-folding macro.

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

**Gap members.** Use a subtraction for gap arrays so the size is self-documenting:

```cpp
undefined m_unk0x05[0x7dc - 0x05];   // 0x05
undefined m_unk0x92c[0x944 - 0x92c]; // 0x92c
```

**Overrides.** Use `override` instead of `virtual` for derived methods (`void VTable0x04() override;`). `override` is defined as empty for MSVC 6.0 in `compat.h`.

## Code Style

- **Bit tests:** `if (flags & c_flagCached)` / `if (!(flags & c_flagCached))` — no `!= 0` / `== 0`.
- **Address padding:** 8 hex digits, lowercase: `0x00449d50`.
- **Annotation ordering:** when a function has both GOLDP and LEGORACERS annotations, GOLDP comes first.
- **No redundant `this->`.** Write `m_member`, `Method()`, `BaseClass::VirtualMethod()` directly. Even `Base::Foo()` to suppress virtual dispatch doesn't need the prefix.
- **Win32 API: prefer un-suffixed names.** Use `CreateWindowEx`, `DEVMODE`, `MSG`, `WIN32_FIND_DATA`, etc. — NOT `CreateWindowExA`/`DEVMODEA`. The un-suffixed names are macros that resolve to the `A` form when `UNICODE` is undefined (project default); the compiled binary still imports the `A` symbols. IDA shows the resolved `*A` symbol — translate back to the macro.
- **Pointer/bool constants:** use `NULL` for null pointer assignments/returns, `TRUE`/`FALSE` for `LegoBool`/`LegoBool32`, and plain `0` only for scalar values and status codes.
- **Blank lines inside functions:** separate decls / setup / main work / return with single blanks; blanks around if/else chains; switch cases stay tightly packed; one-liner bodies need no internal spacing.
- **Enums for magic numbers:** hoist fixed enumerations (flag bits, event tags, state codes) into a named `enum` at class or namespace scope. `c_camelCase` per NCC.
- **No leading `const` on return-by-value** (`const RetType Get() const` — meaningless, trips NCC).

## Naming Conventions

Uses LEGO Island NCC rules (`tools/ncc/ncc.style`), enforced in CI:
- Functions: `FUN_XXXXXXXX` (8 hex digits, lowercase)
- Globals: `g_unk0xXXXXXXXX`
- Members: `m_unk0xXX` (by offset)
- Parameters: `p_unk0xXX`
- Unknown classes: `RandomName0xSize` (random PascalCase + `0x` + hex size, e.g. `NeonCactus0x1d6c`, `VelvetThunder0xc8ac8`)
- Virtual methods: `VTable0xXX` (by vtable offset)
- Enum constants: `c_` prefix
- The `p_`/`m_`/`g_` prefixes apply to *all* parameters/members/globals, not just unknown placeholders (e.g. a named hInstance parameter becomes `p_hInstance`).
- Names must match across prefixes when assigned: `m_hInstance = p_hInstance`, never `m_hInstance = p_something`
- **Unused parameters** must be unnamed in the definition.

## Types

Use Lego types from `util/types.h` for game code:
- `LegoS8`/`LegoU8`, `LegoS16`/`LegoU16`, `LegoS32`/`LegoU32` instead of `char`/`short`/`int` variants
- `LegoFloat`, `LegoChar` (character data), `LegoBool`

Keep original types at API boundaries (Win32, DirectX, CRT); `void*` can remain.

**Unproven types:** use `undefined`/`undefined2`/`undefined4`/`undefined4*` from `decomp.h`. Do not guess `int`/`float`/`void*` until usage context or reccmp proves it.

## Decompiling a New Function

1. **Find the decompilation.** Read the body; note called functions and globals.
2. **Check calling conventions.** Per-call-site guesses can differ from the real definition — cross-reference. `__thiscall` ⇒ class member.
3. **Identify classes from `__thiscall` on a global.** That global is a class instance; declare a class with `undefined m_unk0x00[size]`.
4. **STUB every unknown callee.** Required for build + reccmp. Stubs ordered by address ascending per file.
5. **Avoid fold collisions.** Use the `STUB(0xADDRESS)` macro (from `decomp.h`) in stub bodies to prevent COMDAT folding. Empty destructors are exempt.
6. **Write clean C++, not IDA pseudocode.** Translate `*(_DWORD*)(this + 4)` into proper member access, method calls, named variables.
7. **Build with double `cmake --build`**, then `reccmp-reccmp --target LEGORACERS --verbose 0xADDRESS --print-rec-addr`. Iterate to 100%.
7b. **Verify global data** with `reccmp-datacmp`.
8. **Validate vtables.** `reccmp-reccmp --verbose 0xVTABLE_ADDR`. Every declared virtual needs a matching `// STUB:` with its real address from the original binary.
9. **Check for regressions.** Re-verify previously matched functions that touch modified classes (especially those making virtual calls).
10. **Lint.** `reccmp-decomplint` from `build/`, passing the source directory as a path argument.

## Decompilation Principles

- **Every type must be corroborated by matched code.** A type is proven only when a `// FUNCTION:` using it reaches 100%. Until then, `undefined`/`undefined4`.
- **No raw pointer arithmetic as a substitute for types.** Casts + subtractions mean the types are wrong; find the real class so the cast is legitimate C++ (including multi-inheritance cross-casts — define the inheritance, don't fake the adjustment).
- **One root type per header.** A header should define at most one top-level class or struct; forward declarations do not count. If a second concrete root type is needed, move it to its own header and include that header.
- **Nest one-owner helper types.** Loader params, callback shims, small related records, and similar one-owner types belong inside the primary class that owns or consumes them instead of becoming top-level classes/structs.
- **Ground polymorphic classes.** When a concrete polymorphic class is identified, add its `VTABLE`, ctor, dtor, and scalar-deleting-destructor annotations instead of leaving it as an unannotated interface shape.
- **Read the original binary directly** (Python/struct) for vtable entries, call targets, and function addresses when IDA/Ghidra mislabels them.
- **Every annotation has a real address** — no placeholders.
- **`// FUNCTION:` means 100% match.** Any diff ⇒ the code is wrong; investigate the root cause (layout, types, missing base).
- **Validate with `reccmp-vtable`** in addition to `reccmp-reccmp` — reveals missing/wrong virtual declarations.
- **Inline base constructors.** MSVC 6.0 inlines small base ctors; their code appears between the outer base ctor call and the derived vtable set.

## Prioritize Constructors, Destructors, and SDDs

When starting a new class, match ctor + dtor + scalar-deleting-destructor first. Ctors reveal member init order, base chain (via vtable sets), and types; dtors reveal cleanup order and virtual calls (confirming vtable layout); SDDs verify class size and dtor linkage. Matching these three gives high confidence that size/inheritance/vtable/members are correct before tackling methods.

## MSVC 6.0 Codegen Patterns

### Register allocation: common levers

Register allocation is sensitive to many equivalent-looking source variants. When a function matches behaviorally but registers swap, try:

- **Inline getter vs. direct member access.** Promoting `ptr->m_foo` to `ptr->GetFoo()` (with an inline getter in the class header) — or the reverse — often shifts register choices even though the inlined body is identical. Useful both for cross-object access *and* inside the owning class. Try both directions.
- **Redundant member-pointer aliases.** If a local pointer is assigned directly from a member and then only null-checked or immediately dereferenced (`T* tmp = m_member; if (tmp) tmp->Call();`), first try direct member access (`if (m_member) m_member->Call();`). MSVC 6.0 often emits the same code, and the direct form better reflects human source. Keep the local when it is a real snapshot before mutation, an iterator, a return value, or must be addressable.
- **Expression folding vs. temp local.** `acc += p_str[i] << shift;` vs. `int v = p_str[i] << shift; acc += v;` land the accumulator in different registers (esi vs. eax), cascading to `this` and other hot locals.
- **Clean argument locals can fix scratch-register diffs.** Around COM/virtual calls, introducing a named local for a member argument (`LPDIRECTDRAWSURFACE surface = p_depthBuffer->m_surface;`) can move the same value through the original scratch register without casts, volatility, or assembly.
- **Loop form.** `while (ptr)` / `do-while` put the condition variable in the first callee-saved reg (ebx), pushing `this` to later registers. `for (;;)` + `break` frees ebx for `this`. Swap when allocation doesn't match.
- **Loop-back shape identifies the source form.** `test reg,reg; jne loop_top` on a pointer updated inside the loop ⇒ `while (ptr)` / `do-while (ptr)`, not `for(;;)` + break. IDA's `while (v6 != (char *)-1)` is misleading; the asm tests `!= 0`.
- **Loop-index scope.** Declare `LegoU32 i;` at function scope, not inside `for (;;)`. MSVC 6.0 legacy scoping lets a second `for (i = ...)` reuse it, but CI clang-tidy uses ANSI scoping and rejects the second reference.
- **Strength-reduced loop locals may not be source locals.** When the original has a walking pointer, a one-based induction variable, and a separately incremented derived value, first try the simpler human loop: `for (i = 0; i < N; i++)` over the array, with derived values like `(i * 2) + 1` and adjacent indices `i - 1` / `i + 1`. MSVC 6.0 can synthesize the walking pointer, one-based index, and derived counter; reifying every observed register/stack local in source can make the match worse.
- **Return type.** If the original's epilogue lacks `mov eax, <value>` and yours has one, declare the function `void`. IDA's return-type guess is often just "whatever lingered in eax from the tail call" — see "Return type inference" below.
- **`else if` layout.** A redundant `jne` whose flags come from a much earlier `cmp` (e.g. `cmp ebp, 0xc; jae label; ...; label: jne skip; body; skip:`) signals an `else if` chain — usually `if (x < N) { main } else if (x == N) { body }`, with the `else if` body physically at the end of the block. Also see "Cold-branch layout" below.
- **Clamp+center.** For `if (cond) clamp; else center;`, write clamp as THEN (not ELSE) to match MSVC 6.0 layout.
- **`else if (!cond)` inverts block layout (cold-branch).** When the body of a branch is placed physically AFTER the function's `ret` (reached via forward jump + `jmp` back), MSVC treated it as cold. Reproduce with `if (!X) { hot_body } else if (cond) { cold_body }` — the natural `if (X) { cold } else { hot }` produces inline layout instead.
- **Byte-loop hash accumulator.** Use `LegoChar c = p_str[i]; acc += c << shift;`, not `int v = p_str[i] << shift; acc += v;`.
- **Mutate the parameter; save the original.** When a function needs both `p_arg & MASK` (the hot value, used for indexing and comparison) and the unmasked `p_arg` (cold, used once — e.g. a tail call to `Base::Method`), write `undefined4 saved = p_arg; p_arg &= MASK;` and pass `saved` to the base. The mirror form (`undefined4 masked = p_arg & MASK; ... Base::Method(p_arg, ...)`) regresses ~16pp because MSVC 6.0 pins the parameter register (typically ebp) to the incoming value, so introducing a new local for the masked value forces a second register allocation and inverts scratch-register choices around adjacent indexed member loads (e.g. ecx ↔ edi swap on `m_member[idx]`). Diagnostic: if you're stuck near 80–85% with the diff concentrated on register roles around an indexed access, this is the first variant to try.
- **Hoist computed values to locals before unrelated stores or copies.** When a function interleaves a computed value (FPU multiply/divide/sqrt, an arithmetic expression, a member load with displacement, a `lea`, etc.) with stores or struct copies that touch a different register file, MSVC 6.0's scheduler may emit the operations in a different order than the original. Hoist the computed value to a named local *before* the unrelated work: `T tmp = expensive_compute(); obj->other_field = src->other_field; obj->target = tmp;`. The compiler then issues the compute early, lets the unrelated work run in parallel ("in flight"), and stores the result late. This works for FPU↔integer interleaving (e.g. `obj->float_squared = x * x; obj->vec = src->vec;` → hoist the multiply), and similarly for any pair where the original asm shows two independent computations woven together. Diagnostic: if the diff is just an instruction-encoding choice (e.g. `mov [base+disp]` vs `mov [reg]`) on the *first* store after a `lea` or expression, the preceding compute is being scheduled differently — try hoisting it. Rule of thumb: if hoisting one helps, hoist *all* the independent precomputes so the entire schedule is established before the bulk stores begin.
- **Local declaration position controls callee-saved push timing.** MSVC 6.0 decides *when* to emit `push <callee-saved reg>` based on where in the source the value living in that register first becomes needed. Declaring a local at function entry (e.g. `LegoBool32 result = FALSE;` or `Type* p = NULL;`) — even one not yet used — pushes the register up front; declaring it later defers the push past intervening early returns. This may matter when the diff shows a register being pushed/popped at different points in mine vs the original, *and* when the original uses that register as an accumulator (e.g. `xor edi, edi` at entry, `mov edi, 1; mov eax, edi` at returns) while mine bypasses it (`pop edi; mov eax, 1`). When that pattern fits, declaring the accumulator local *before* any early-return check, plus writing the special path as a direct `if (cond) return CONST;` (so the constant return doesn't go through the accumulator) while leaving other paths to set/return the local, can align both halves at once. May not apply: many functions use callee-saved regs for unrelated reasons, and forcing an early declaration where the original kept the value scoped tighter can regress the match.

### Return type inference

- `mov eax, <literal>` in the epilogue ⇒ the function returns that literal; declaring it `void` will mismatch. Often `LegoS32` returning a success sentinel.
- Conversely, no `mov eax, ...` in the epilogue and IDA still reports `int`: the tail-call's return value lingers in eax; the original was `void`. Flip and the match often jumps from <95% to 100%.
- **Float literal assignments may compile to integer `mov`.** `float_member = 1.0f` under /O2 compiles to `mov dword ptr [offset], 0x3F800000`, not `fld`/`fstp`. `LegoFloat` members with float literals produce the correct integer stores.

### Vtable and SDD reading

- **Vtable set position proves class hierarchy.** MSVC 6.0 sets the vtable at the start of the ctor body, *after* all base ctors. A vtable set that appears *after* some member init means that init belongs to an inlined base ctor.
- **Double vtable set in a ctor = inheritance.** `*this = off_BASE; <sub_ctor_calls>; *this = off_DERIVED; <body>` — first is the inlined base ctor, second is the derived vtable. Two `mov [ecx], &vtable` writes identify the inheritance chain.
- **Vtable-set-at-dtor-start is orthogonal to virtual-dtor.** Any polymorphic class writes its own vftable at dtor entry (so virtual calls during destruction resolve locally), whether the dtor itself is virtual or not. Check the vtable for an SDD slot to determine virtuality.
- **Virtual dtor placement.** MSVC places the SDD at slot N (the first new slot past inherited ones). Other virtuals declared before `~Derived()` in the class body take earlier slots and push the SDD later — declaration order matters.
- **SDD body pattern.** `push esi; mov esi, ecx; call <dtor>; test byte ptr [esp+8], 1; je .skip; push esi; call operator delete; add esp, 4; .skip: mov eax, esi; pop esi; ret 4`. When a vtable slot points to this shape, declare a virtual dtor and add `// SYNTHETIC: MODULE 0xADDR` in the class. A larger body with unrelated sub-calls is a regular virtual (`VTable0xNN`), not a dtor.
- **`delete obj` vs. `obj->SlotNMethod(1)`** compile to identical bytes (`mov edx, [ecx]; push 1; call [edx+SDD_OFFSET]`) when slot N is the SDD's slot. They differ only in whether eax is consumed. If the enclosing function uses the SDD's return, write the virtual-call form; otherwise use `delete`.
- **Typed sub-object members auto-emit ctor/dtor calls.** Prefer `SubClass m_member;` over byte arrays. MSVC emits the sub-ctor in the outer ctor at the member's offset (in declaration order) and the sub-dtor in the outer dtor (reverse order). If the sub-class ctor/dtor has a correct STUB address, reccmp resolves the outer's calls and the outer can reach 100% — verifying the sub-object's offset without implementing its body. This is the primary tool for verifying class layout.

### SEH emission in constructors

- **Cross-TU visibility gates SEH.** MSVC emits the SEH frame prologue (`push -1; push __ehhandler; mov fs:[0], esp; ...`) in a ctor only if it cannot prove the sub-ctors are no-throw. Sub-classes defined in the SAME .cpp ⇒ compiler inspects bodies (e.g. `STUB` macro is a trivial global write → no-throw) and elides SEH. Moving sub-classes to SEPARATE .cpp files hides the bodies and forces SEH emission.
- **Counter size reflects dtor-bearing member count.** MSVC writes a small integer to a stack slot (usually `[esp+0x10]`) as each dtor-bearing member is constructed — N+1 states for N members. If the original has 3 counter stores (`-1`, `0`, `1`) but yours has 2, you're missing a member dtor.

### Call-site signals

- **`mov ecx, X; call F` indicates `__thiscall`** — even if F never reads `this`. Declare F as a non-static member of the class whose pointer is in ecx; the body can ignore `this`. No `mov ecx` before the call ⇒ NOT `__thiscall`.
- **Direct call to a folded empty method = explicit base-scope call.** `call <addr>` (opcode `e8`) where `<addr>` is the landing pad for empty `void f()` thiscalls (e.g. `0x4164C0` in LEGORACERS) is `BaseClass::VTable0xNN();` inside a derived member. The explicit `Base::` suppresses virtual dispatch. A virtual call emits `mov eax, [ecx]; call [eax+N]` — very different bytes.
- **MSVC 6.0 does NOT tail-call `__cdecl`.** A trivial `int Outer(a,b,c,d) { return Inner(a,b,c,d); }` emits a ~30-byte re-push + call + epilogue, not `jmp Inner`. Only `__thiscall` tail-calls (`~Class() { Release(); }` → 5-byte `jmp`). Plan for real wrapper + impl when the binary shows this double-dispatch between `__cdecl` functions.
- **Static member functions emit identical bytes to free `__cdecl`.** Moving a free function into a class as a static member needs no codegen change; update call sites only.
- **MSVC 6.0 rejects `__thiscall` on function pointer typedefs** (C4234). Use a member function pointer (`typedef int (Class::*MP)(int)`) and write the slot address via `*(void**)&mp = vtable[slot]` — but this emits `mov reg, [vtable+slot]; call reg`, not the direct `call [vtable+slot]` a named virtual call produces. When byte-exact match matters, declare a named `virtual` at the slot instead.
- **Overload by `int` vs. typedef'd unsigned int.** `int` (signed) and `LegoBool32`/`LegoU32` (unsigned) are distinct under overload resolution despite identical storage. Use to split a tiny `__cdecl` wrapper and same-signature impl — the wrapper casts to force the overload. Without the cast, overload resolution picks itself and recurses.
- **IDA's FLIRT can mislabel local functions as STL/MSVCRT symbols.** Verify by checking the PE import table — if the name isn't imported, it isn't external. Disassemble the `e8 <rel32>` at the call site to find the real target; if it's in the executable's own code range, it's local. STUB a typed sub-object member at that address and the outer ctor/dtor can match without any STL dependency.
- **Late `[esp+N]` loads near the epilogue may still be the incoming stack arg.** Recount pushes/calls before assuming the load is a nearby local struct field; in `__thiscall` methods the original parameter can still be sitting above locals after several API calls.
- **Byte-identical call setup but different `call rel32` target = thunk annotation gap.** If the pushes and surrounding stores match exactly and only the direct call destination differs, the caller is probably correct; annotate the import thunk in `library_msvc.h` instead of distorting the source.
- **`__purecall` in a derived vtable ⇒ re-pure-virtualize.** A derived class can redeclare a concrete base virtual as pure (`override = 0`), putting `__purecall` in the derived slot while keeping the base body reachable via explicit `Base::Method()`.
- **Derived-override tail calls to base: trace the spill.** When a derived override ends in `Base::Method(...)`, check what the original pushes at that arg slot. A stack-spilled local in the original versus a literal `FALSE`/`0` in your source collapses the match.
- **Inferring signatures from push sequence.** Arg count = number of `push <reg>` before the `call`/`call [vtable+N]`; right-to-left push order = first-to-last arg. A caller push with no matching param in your declaration means your signature has too few args. For callback interfaces tightly coupled to one outer class, prefer a nested class (`Outer::Callback`).

### Layout and member diagnostics

- **Walking-pointer base reveals true struct layout.** When iterating an array of structs, MSVC seeds the walking pointer with `lea reg, [this + K]` where K centers on the hottest access region (typically the middle of the first triplet of accesses). A uniform `Δ`-byte shift between your `[reg+disp]` and the original's means your struct base is wrong by `Δ` bytes — shift the outer-class array declaration backward by `Δ` and pad each inner struct's head with `Δ` extra bytes to preserve size.
- **Fused memset across adjacent members of different types.** When the original emits one contiguous zero-store spanning two adjacent members, two separate `memset` calls won't fuse. Use one call sized `sizeof(first) + sizeof(second)` with a short comment, or nest the members in a struct so one `sizeof(whole)` covers the block.
- **`ZeroMemory` can beat aggregate init for Win32/DirectX structs.** `Type s; ZeroMemory(&s, sizeof(s)); s.dwSize = ...;` can match stack-store order that `{0}` and field-by-field zeroing miss, especially for descriptor structs like `DSBUFFERDESC`.
- **Small fixed-size `memcmp` as a clean inline compare.** For small constant sizes, MSVC 6.0 can inline `memcmp(ptrA, ptrB, N)` into pointer-address loads and scalar compares instead of emitting a library call. This is useful when the original loads buffer addresses into registers before dereferencing; a hand-written casted load such as `*(LegoU32*)ptrA != *(LegoU32*)ptrB` may instead compile to direct global memory operands and miss. Verify the exact size-specific lowering with reccmp, and keep unrelated global scratch buffers as separate declarations rather than widening an existing buffer, since changing a global object's declared size can perturb register allocation in other functions that use it.
- **Branch-free select that resists forcing.** A ternary selecting between a small literal and zero prefers branch-free `neg; sbb; and` under /O2; no conventional source (if/else, volatile) reliably forces the branch form. Accept partial match when this is the only diff. `char` storage still recovers the `movsx` half.
- **Preventing unwanted ICF with `#pragma code_seg` (temporary hack).** Symptom: reccmp "Failed to find function symbol" + a derived vtable slot points to a fold survivor. Wrap each affected function in a uniquely-named code section:
  ```cpp
  // TODO: Temporary workaround until we figure out how the original code was written.
  #pragma code_seg(".text$unique_suffix")
  RetType Class::Method() { ... }
  #pragma code_seg()
  ```
  Do NOT use for functions the original itself folds — those stay `FOLDED`.

### Misc

- **`sizeOfArray(m_member)` for loop bounds.** Compile-time evaluated to the same immediate as a hard-coded count, but self-documenting and robust to resizes.
- **Write human-readable code, not IDA pseudocode.** No gotos, no raw float bit patterns. Iterate with reccmp to ensure the clean form still matches.

## COMDAT Folding Across Targets

A function in `common/src/` compiled into both targets can need different fold groups per target — e.g. a trivial `return 0;` that folds with empty STUBs in one target but stays independent in the other. Wrap `STUB()` in `#ifdef BUILDING_GOL` and annotate both targets:

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

In GOLDP the `STUB(...)` write makes the body match other `STUB(0xAAAAAAAA)` and they fold; in LEGORACERS the macro is gone and the standalone `xor eax, eax; ret` matches at its own address.

## Vtable annotation syntax

Class-header annotations require the colon: `// VTABLE: MODULE 0xADDRESS`, not `// VTABLE MODULE 0xADDRESS`. reccmp silently ignores the colonless form and vtable set sites inside dtors/ctors show up as `<OFFSET2>` instead of `ClassName::vftable`, costing 5–10% match. Same rule for `// FUNCTION:`, `// STUB:`, `// GLOBAL:`, `// SYNTHETIC:`. `// SIZE` is the exception — no colon.

## Shared Common Code Inlining

`common/src/` is compiled as separate object targets for GOLDP and LEGORACERS. This lets project-level compiler settings express target-specific codegen while keeping one idiomatic source implementation.

Current pattern:

- `common_goldp` compiles `COMMON_SOURCES` with `BUILDING_GOL` and `/Ob2`.
- `common_legoracers` compiles the same `COMMON_SOURCES` with `BUILDING_LEGORACERS` and the default inline behavior.
- `goldp` and `legoracers` link the corresponding common object target.
- `GOLDP_INLINE_EXPANSION_SOURCES` is a small evidence-driven list of GOLDP-only source units compiled with `/Ob2`. Treat it as a placeholder for a possible original static library or project grouping; this is not proven yet. These units keep standalone functions while MSVC also inlines them into compiler-generated callers such as scalar deleting destructors. Keep the list narrow, and do not broaden `/Ob2` to the full `goldp` target because that changes unrelated GOLDP codegen.

Do not steer common-code matches by duplicating implementations, moving selected functions into headers, adding `.inl.h` files, or using `#pragma inline_depth`. If a common function differs between GOLDP and LEGORACERS because of inlining, first verify whether it belongs to this target-level common-source pattern.

## Naming Members from Matched Code

A member name is proven when a `// FUNCTION:` match forces a specific semantic interpretation — e.g. a member that is both `count++` inside a loop bounded at 20 AND stored into `g_fileSourceCount` is unambiguously a file-source count. Rename the `m_unk0xNN` placeholder once a match corroborates usage. Member *types* still follow the `undefined`/`undefined4` rule.

## Naming Functions from Matched Code

Rename from `VTable0xNN` / `FUN_XXXXXXXX` to a semantic name when evidence is strong:

- **Clear pair with a named counterpart.** `VTable0x20` calls `m_input.Shutdown()`; adjacent `VTable0x1c` calls the input-init helper with hInstance/hWnd → `VTable0x1c` is `InitInput`.
- **Symmetric with a named method.** `VTable0x10` undoes every action `Init()` took and is also `~Class()` body → `Destroy`.
- **Body leaves no interpretation.** A one-line tail call to `InitInput`, or a loop opening every line of a newline list and publishing them as globals.

Do not rename on weak evidence. If multiple plausible names exist (`OpenFileSources` vs. `LoadFileSources` vs. `RegisterFileSources`), keep `FUN_XXXXXXXX`. A misleading name is worse than a neutral placeholder. Renaming a virtual does not affect codegen — the vtable is slot-indexed — so it's safe if all call sites and overrides are updated together.

**Lifecycle vocabulary.** Match existing class method names so the whole codebase shares one vocabulary:

- `Init()` — explicit init separate from the ctor (ctor zeroes fields, `Init` allocates/loads/registers).
- `Run()` — the main loop / per-instance driver (top-level app/game class).
- `Shutdown()` — release live resources but leave the object reusable (`SoundManager`, `CobaltMist0x30`, `OpalVault0xf0`, `IndigoStar0x18`, `GolHashTable`).
- `Destroy()` — full teardown: invokes `Shutdown` plus everything else, leaving the object in its post-construction state.
- `Reset()` — return to pristine zero-state (shared between ctor/dtor bodies, e.g. `CrimsonForge0x800::Reset`).

When a class has a small subsystem-teardown method AND a larger full-destroy wrapper, the small one is `Shutdown` and the big one is `Destroy` — even if it means renaming a previously-named `Shutdown` to `Destroy`. Don't invent `Cleanup` / `Teardown` / `StopServices`.

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
