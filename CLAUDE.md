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
reccmp-reccmp --target LEGORACERS --total 3986 --nolib -S LEGORACERSPROGRESS.SVG
reccmp-reccmp --target GOLDP --total 1071 --nolib -S GOLDPPROGRESS.SVG

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

**The colon is required** for every annotation except `// SIZE`. reccmp silently ignores `// VTABLE MODULE 0x...` (no colon); vtable set sites inside ctors/dtors then show as `<OFFSET2>` instead of `ClassName::vftable`, costing 5–10% match.

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
- **Blank lines inside functions:** write functions in readable paragraphs. Keep tight sequences of the same kind together (member assignments, descriptor field setup, argument pushes mirrored as calls), but separate declarations/setup, the main operation, and result-handling blocks with single blank lines. If a local result is introduced after setup, put a blank line before it. If an `if`/loop block closes and the next statement is a `return`, put a blank line before the `return`; returns inside a block after ordinary statements stay tight. Switch cases and tiny one-liner bodies stay tightly packed.
- **Enums for magic numbers:** hoist fixed enumerations (flag bits, event tags, state codes) into a named `enum` at class or namespace scope. `c_camelCase` per NCC.
- **No leading `const` on return-by-value** (`const RetType Get() const` — meaningless, trips NCC).
- **clang-format the files you touch** (CI-enforced; reflowing is codegen-neutral). NCC naming runs in CI only.

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

1. **Find the decompilation and check the byte budget.** Read the body; note called functions and globals. The gap to the next function's address bounds the implementation — a rich decompiled body that cannot fit means the function is a thin wrapper and the real logic lives in a callee (often a nearby unannotated address). Disassemble suspicious gaps before writing code.
2. **Check calling conventions.** Per-call-site guesses can differ from the real definition — cross-reference. `__thiscall` ⇒ class member.
3. **Identify classes from `__thiscall` on a global.** That global is a class instance; declare a class with `undefined m_unk0x00[size]`.
4. **STUB every unknown callee.** Required for build + reccmp. Stubs ordered by address ascending per file.
5. **Avoid fold collisions.** Use the `STUB(0xADDRESS)` macro (from `decomp.h`) in stub bodies to prevent COMDAT folding. Empty destructors are exempt.
6. **Write clean C++, not IDA pseudocode.** Translate `*(_DWORD*)(this + 4)` into proper member access, method calls, named variables. No gotos, no raw float bit patterns.
7. **Build with double `cmake --build`**, then `reccmp-reccmp --target LEGORACERS --verbose 0xADDRESS --print-rec-addr`. Iterate to 100%.
7b. **Verify global data** with `reccmp-datacmp`.
8. **Validate vtables.** `reccmp-reccmp --verbose 0xVTABLE_ADDR`. Every declared virtual needs a matching `// STUB:` with its real address from the original binary.
9. **Check for regressions.** Re-verify previously matched functions that touch modified classes (especially those making virtual calls).
10. **Lint.** `reccmp-decomplint` from `build/`, passing the source directory as a path argument.

## Decompilation Principles

- **Every type must be corroborated by matched code.** A type is proven only when a `// FUNCTION:` using it reaches 100%. Until then, `undefined`/`undefined4`.
- **No raw pointer arithmetic as a substitute for types.** Casts + subtractions mean the types are wrong; find the real class so the cast is legitimate C++ (including multi-inheritance cross-casts — define the inheritance, don't fake the adjustment).
- **Split mixed compilation units until unexplained address gaps are gone.** A large non-FOLDED address jump usually means a function is assigned to the wrong class, or multiple classes are mashed into one source unit. Move whole classes (or cohesive groups) into address-local implementation units; never split one class's methods across `.cpp` files just to tidy address order. Interleaved ranges prove nested-class TUs: when a nested class's methods occupy a range separated from the enclosing class's functions by a *different file's* range, give the nested class its own `.cpp` (the type stays nested in the header).
- **One root type per header.** A header should define at most one top-level class or struct; forward declarations do not count. If a second concrete root type is needed, move it to its own header and include that header.
- **Nest one-owner helper types.** Loader params, callback shims, small related records, and similar one-owner types belong inside the primary class that owns or consumes them instead of becoming top-level classes/structs.
- **Ground polymorphic classes.** When a concrete polymorphic class is identified, add its `VTABLE`, ctor, dtor, and scalar-deleting-destructor annotations instead of leaving it as an unannotated interface shape.
- **Read the original binary directly** (Python/struct/capstone) for vtable entries, call targets, and function addresses when IDA/Ghidra mislabels them. Disassembler dumps stop at the first `ret` — a function can continue past it.
- **Every annotation has a real address** — no placeholders.
- **`// FUNCTION:` means 100% match.** Any diff ⇒ the code is wrong; investigate the root cause (layout, types, missing base).
- **Re-verify inherited matches.** When reviewing a branch or integrating generated code, re-measure every `// FUNCTION:` claim with reccmp — claimed matches are not verified matches; demote sub-100% claims or fix them.
- **Validate vtables explicitly** (verbose compare on the vtable address) in addition to function compares — reveals missing/wrong virtual declarations.
- **Inline base constructors.** MSVC 6.0 inlines small base ctors; their code appears between the outer base ctor call and the derived vtable set.

## Prioritize Constructors, Destructors, and SDDs

When starting a new class, match ctor + dtor + scalar-deleting-destructor first. Ctors reveal member init order, base chain (via vtable sets), and types; dtors reveal cleanup order and virtual calls (confirming vtable layout); SDDs verify class size and dtor linkage. Matching these three gives high confidence that size/inheritance/vtable/members are correct before tackling methods.

## MSVC 6.0 Codegen Patterns

### Register allocation: common levers

Register allocation is sensitive to many equivalent-looking source variants. When a function matches behaviorally but registers swap, try:

- **Expression folding vs. temp local.** `acc += p_str[i] << shift;` vs. `int v = p_str[i] << shift; acc += v;` land the accumulator in different registers, cascading to `this` and other hot locals. Keep byte values in byte-typed locals (`LegoChar c = p_str[i]; acc += c << shift;`).
- **Redundant member-pointer aliases.** Prefer direct member access (`if (m_member) m_member->Call();`) over `T* tmp = m_member; if (tmp) tmp->Call();` — usually identical codegen and closer to human source. Keep the local only for a real snapshot-before-mutation, an iterator, a return value, or an addressable call argument.
- **Clean argument locals can fix scratch-register diffs.** Around COM/virtual calls, a named local for a member argument (`LPDIRECTDRAWSURFACE surface = p_depthBuffer->m_surface;`) can route the value through the original scratch register without casts or volatility.
- **Mutate the parameter; save the original.** When a function needs a masked form of `p_arg` as the hot value and the raw value once (cold), write `undefined4 saved = p_arg; p_arg &= MASK;` — not a new local for the masked value. MSVC pins the parameter register to the incoming value; the mirror form inverts scratch registers around indexed accesses (~16pp). Diagnostic: stuck near 80–85% with the diff concentrated on register roles around an indexed access.
- **Mutate address-taken out-params for follow-up math.** When the original stores derived values into the same stack slots as `GetPlacement(&x, &y, ...)` out-args, the source reassigned them (`x = p_x + i - x;`). Address-taken locals are memory-homed, so reassignment emits the store; fresh locals stay in registers, dropping the stores and shortening the function.
- **Hoist computed values to locals before unrelated stores/copies.** When the original interleaves an independent computation (FPU op, `lea`, member load) with stores touching a different register file, hoist it: `T tmp = compute(); obj->other = src->other; obj->target = tmp;`. Diagnostic: an instruction-encoding diff (`mov [base+disp]` vs `mov [reg]`) on the first store after a `lea`/expression. If hoisting one helps, hoist all the independent precomputes.
- **Paired independent stores emit in reverse source order.** Two adjacent independent member assignments load both sources first, then store the *second* statement's target first. If your two stores are swapped vs. the original, swap the source statements.
- **Local declaration position controls callee-saved push timing.** A local initialized at function entry pushes its register up front; declaring it later defers the push past early returns. When the original uses a callee-saved accumulator (`xor edi,edi` at entry; `mov edi,1; mov eax,edi` at returns), declare the accumulator before the early-return checks and write the special path as a direct `return CONST;`. Can also regress — try both positions.
- **Constant-zero unification.** If your build compares via a zeroed register (`xor ecx,ecx; cmp eax,ecx`) where the original uses load + `test eax,eax` and stores zero-inits as immediates, MSVC unified one zero across an init and a comparison. Reposition the `= 0` declaration or raise loop register pressure (e.g. a named index local) so the shared zero register stops paying off.
- **Statement position flips stuck two-register mirrors.** Moving a statement across an adjacent block (e.g. an assignment before vs. after an `if`) changes a live range's endpoint and can flip a coloring no declaration shuffle fixes. Likewise a mutation appearing before a test that doesn't consume it (`lower += p_height;` ahead of a skip check) is literal source order — keep it there.
- **Return type.** If the original's epilogue lacks `mov eax, <value>` and yours has one, declare the function `void` (see "Return type inference").

### Loops and indexing

- **Start from the natural indexed source.** Walking pointers, one-based induction variables, and separately incremented byte/element offsets are usually MSVC strength reduction, not source locals. Begin with `for (i = 0; i < N; i++)` and direct indexed uses (`items[i].field`, `i - 1`, `(i * 2) + 1`); introduce per-iteration aliases (`T& item = items[i]`) or explicit walking pointers only when the indexed form demonstrably fails (real snapshot, stable pointer register, addressable argument). Reifying every observed register in source usually makes the match worse.
- **Named index local for repeated element access.** When the same `m_entries[expr]` element is touched several times — especially across a call — `LegoS32 index = expr;` materializes the strength-reduced byte offset (`lea r,[i+i*2]; shl r,2`) in a callee-saved register that survives the call, and demotes competing values (cached params, hoisted sums) so `this` keeps its original register. Diagnostic: your build recomputes the index per use, or caches `p_x`/`p_y` in callee-saved regs where the original reloads them from arg slots.
- **Multiply operand order is visible.** `member * expr` loads the member into a register first (`imul reg, reg`); `expr * member` emits `imul reg, [member]`. The same binary mixes forms function-by-function — read each site.
- **Loop form.** `while (ptr)` / `do-while` put the condition variable in the first callee-saved reg (ebx), pushing `this` later; `for (;;)` + `break` frees ebx for `this`. Loop-back shape `test reg,reg; jne top` ⇒ `while (ptr)` / `do-while`, not `for(;;)`+break (IDA's odd loop conditions notwithstanding).
- **Loop-counter scope.** Two `for (LegoS32 i = ...)` in the *same* scope are a redefinition under MSVC legacy scoping — declare `LegoS32 i;` once at function scope and reuse. Sibling branch arms may each declare their own counter; choose by the original's counter homes: arms sharing one stack slot ⇒ a single function-top declaration; distinct homes (slot+restore in one arm, register-only in the other) ⇒ per-arm `for`-init declarations.
- **`for (i = m_count++; i > p_index; i--)`** folds an increment into the loop init (load old value, compare on it, store old+1). A separate `m_count++;` statement emits `inc` plus an explicit `new - 1`.
- **`sizeOfArray(m_member)` for loop bounds** — compiles to the same immediate as a hard-coded count, self-documenting.

### Inline member helpers

Small inline-defined class methods are a matching tool of their own — expansions behave differently from equivalent inline expressions:

- **Getter vs. direct member access.** Promoting `ptr->m_foo` to an inline `ptr->GetFoo()` (or the reverse) shifts register choices even though the body is identical. Try both directions.
- **Control flow evaluated twice in one condition = inline helper.** A condition evaluating the same clamp/select twice, branchy both times (`cmp/jle/xor` per evaluation, operand masks CSE'd), cannot be a ternary: ternaries compile branch-free (`setcc`/`sbb`/`shr`) and CSE into one evaluation. Write an inline helper with the `if` inside (`LegoS32 GetClampedLower() { LegoS32 v = m_second & 0x3f; if (v > (m_first & 0x3f)) v = 0; return v; }`) and call it in each operand — inlined control flow is not CSE'd, and each expansion is branchy.
- **Branchy 1/0 store through one address = inline setter.** `if/else` statement stores reload the array base per arm; a ternary store compiles to `shr`. One address computation feeding branchy `mov byte [r+8], 1/0` stores = an inline setter taking the flag byte (`void SetOccupied(LegoU8 p_flags) { if (p_flags & 0x80) ... else ... }`).
- This family also resolves the "branch-free select" dead end: a bare ternary between a literal and zero resists all statement-level forcing (accept the partial match only if no helper fits; `char` storage still recovers a `movsx` half).

### Branch layout and shared epilogues

- **`else if` layout.** A redundant `jne` whose flags come from a much earlier `cmp` signals an `else if` chain — usually `if (x < N) { main } else if (x == N) { body }`, with the `else if` body physically last.
- **Cold-branch inversion.** A branch body placed after the function's `ret` (forward jump + `jmp` back) was treated as cold; reproduce with `if (!X) { hot } else if (cond) { cold }` — the natural `if (X) { cold } else { hot }` stays inline. For `if (cond) clamp; else center;`, write clamp as THEN.
- **Identical early returns merge only as one statement.** MSVC emits a separate inline epilogue per `return CONST;` statement; it does not cross-jump them. When the original's early check jumps forward *into* a later return's epilogue, restructure so both paths flow through a single return statement — e.g. `if (height >= 0) { ...error-code returns... } return height;` rather than an early `if (height < 0) return height;`.
- **Merged failure paths have expression-level sources.** A retry whose double-failure shares another failure's `result = FALSE;` block compiles from assignment-in-condition: `if (x == -1 && (x = Retry()) == -1) { result = FALSE; } else { ... }`. A check that jumps directly behind another path's cleanup call comes from a comma side-effect: `if (count > 64 || (!Initialize(64) && (Clear(), TRUE))) { return FALSE; }`. Use these only when the original's jump targets prove them.

### Return type inference

- `mov eax, <literal>` in the epilogue ⇒ the function returns that literal; declaring it `void` will mismatch. Often `LegoS32` returning a success sentinel.
- Conversely, no `mov eax, ...` in the epilogue and IDA still reports `int`: the tail-call's return value lingers in eax; the original was `void`. Flip and the match often jumps from <95% to 100%.
- **Pointer returned as boolean.** Failure epilogues `xor eax,eax` while the success path leaves a live pointer in eax ⇒ the function returns the pointer (callers just `test eax,eax`). Declare the pointer return type with `T* result = thing; ... result = NULL; ... return result;`, not `LegoBool32`.
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
- **MSVC 6.0 rejects `__thiscall` on function pointer typedefs** (C4234). A member-function-pointer workaround emits `mov reg, [vtable+slot]; call reg`, not the direct `call [vtable+slot]` of a named virtual call — when byte-exact match matters, declare a named `virtual` at the slot instead.
- **Overload by `int` vs. typedef'd unsigned int.** `int` and `LegoBool32`/`LegoU32` are distinct under overload resolution despite identical storage. Use to split a tiny `__cdecl` wrapper from a same-signature impl — the wrapper casts to force the overload (without the cast it picks itself and recurses).
- **IDA's FLIRT can mislabel local functions as STL/MSVCRT symbols.** If the name isn't in the PE import table, it isn't external; disassemble the `e8 <rel32>` to find the real target. STUB a typed sub-object member at that address and the outer ctor/dtor can match without any STL dependency.
- **Late `[esp+N]` loads near the epilogue may still be the incoming stack arg.** Recount pushes/calls before assuming the load is a nearby local struct field; in `__thiscall` methods the original parameter can still be sitting above locals after several API calls.
- **Byte-identical call setup but different `call rel32` target = thunk annotation gap.** If the pushes and surrounding stores match exactly and only the direct call destination differs, the caller is probably correct; annotate the import thunk in `library_msvc.h` instead of distorting the source.
- **`__purecall` in a derived vtable ⇒ re-pure-virtualize.** A derived class can redeclare a concrete base virtual as pure (`override = 0`), putting `__purecall` in the derived slot while keeping the base body reachable via explicit `Base::Method()`.
- **Derived-override tail calls to base: trace the spill.** When a derived override ends in `Base::Method(...)`, check what the original pushes at that arg slot. A stack-spilled local in the original versus a literal `FALSE`/`0` in your source collapses the match.
- **Inferring signatures from push sequence.** Arg count = number of `push` before the call; right-to-left push order = first-to-last arg. A caller push with no matching param means your signature is short. Mid-sequence `mov ecx, [argslot]` before `call` reveals a `__thiscall` target and which arg is its `this`. For callback interfaces tightly coupled to one outer class, prefer a nested class (`Outer::Callback`).

### Layout and member diagnostics

- **Walking-pointer base reveals true struct layout.** When iterating an array of structs, MSVC seeds the walking pointer with `lea reg, [this + K]` where K centers on the hottest access region. A uniform `Δ`-byte shift between your `[reg+disp]` and the original's means your struct base is wrong by `Δ` bytes — shift the array declaration and pad the struct head to preserve size.
- **Out-of-range member access reveals true struct size.** A method accessing `[this+N]` at or past the believed `SIZE` means the struct is larger — typically absorbing an adjacent "unknown" member of the enclosing class. Resize the nested struct and delete the parent's member; ctors/dtors that never touched the new field keep matching.
- **Stream cursors are members with helpers.** Serialization spread across methods keeps the cursor as a member (`LegoU8* m_cursor`) with small read/write methods (`ReadU16`/`WriteU16`) rather than passing a pointer around. Byte reads promote through *two* locals — `LegoU8 b = *m_cursor++; LegoS32 x = b;` — emitting byte-slot store + immediate dword reload + `and 0xff`. A single `LegoS32` local instead compiles to `xor reg,reg; mov bl,[..]`; a single `LegoU8` local defers the masks to the use sites. Diagnostic: one logical value with two stack homes = two locals.
- **Fused memset across adjacent members of different types.** One contiguous zero-store spanning two members won't come from two `memset` calls — use one call sized `sizeof(first) + sizeof(second)` with a short comment, or nest the members in a struct.
- **`ZeroMemory` can beat aggregate init for Win32/DirectX structs.** `Type s; ZeroMemory(&s, sizeof(s)); s.dwSize = ...;` can match stack-store order that `{0}` and field-by-field zeroing miss.
- **Small fixed-size `memcmp` inlines** into pointer loads + scalar compares; a hand-cast `*(LegoU32*)a != *(LegoU32*)b` compiles to direct global memory operands instead and misses. Don't widen an existing global buffer for scratch space — its declared size perturbs register allocation in other users.
- **ICF folds in two pools: in-class (inline) vs out-of-line — never across.** link 6.00.8168 folds byte-identical COMDATs only within the same kind: methods defined in the class body (SELECT_ANY) fold with each other, out-of-line /Gy functions fold with each other; identical bytes never fold across that boundary. This is why the original keeps the same trivial body at two addresses (e.g. `xor eax,eax; ret 0xc` at 0x466090 and 0x473490). When reccmp shows a GONE fold twin or a vtable slot pointing at a wrong fold survivor, the function is on the wrong SIDE: move its definition in-class (or out-of-line) to match the original pool. Deciding the side: an `e8` direct call to a pool address proves that pool out-of-line (calls to in-class trivial bodies inline away under /Ob1); an inline-pool survivor sits at its first INCLUDER's contribution tail, an out-of-line survivor inside its own TU's range. Never use `#pragma code_seg` section splitting for this. A non-trivial in-class body can still be legitimately e8-called when the caller's size makes /Ob1 decline the inline (GolCameraBase::Dot2) — if our draft caller inlines it instead, the symbol vanishes: keep the in-class form and demote its annotation to `// STUB:` until the caller matches.

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

## Shared Common Code Inlining

`common/src/` is compiled as separate object targets for GOLDP and LEGORACERS. This lets project-level compiler settings express target-specific codegen while keeping one idiomatic source implementation.

Current pattern:

- `common_goldp` compiles `COMMON_SOURCES` with `BUILDING_GOL` and `/Ob2`.
- `common_legoracers` compiles the same `COMMON_SOURCES` with `BUILDING_LEGORACERS` and the default inline behavior.
- `goldp` and `legoracers` link the corresponding common object target.
- `GOLDP_INLINE_EXPANSION_SOURCES` is a small evidence-driven list of GOLDP-only source units compiled with `/Ob2`. Treat it as a placeholder for a possible original static library or project grouping; this is not proven yet. Keep the list narrow, and do not broaden `/Ob2` to the full `goldp` target — that changes unrelated GOLDP codegen.

Do not steer common-code matches by duplicating implementations, moving selected functions into headers, adding `.inl.h` files, or using `#pragma inline_depth`. If a common function differs between GOLDP and LEGORACERS because of inlining, first verify whether it belongs to this target-level common-source pattern.

## Float Constants: Literals vs Named Globals

Proven by experiment (cl 12.00.8168 `/O2`) and by census of the original binaries.

**Compiler behavior.**

- **Literals** are per-value COMDATs: deduped within a TU and merged across TUs by the linker — one address per value per binary. Codegen: pure FPU uses keep the constant as the *memory operand* (`fld arg; fmul [pool]`); stores are immediate (`mov [dst], 0x3f000000`); args are immediate (`push 0x3f000000`); constant expressions fold (`x = 0.5f; x = -x` compiles to a pooled `-0.5`).
- **Named const globals** (`static const` and `extern const` behave identically): never fold, never merge, live in `.rdata`. `fmul`/`fadd` load the constant FIRST (`fld [g]; fmul arg`); stores/pushes go through a register (`mov eax, [g]; push eax`); negation emits `fld [g]; fchs`.
- **Writable `.data` floats** are named non-const globals; codegen like named consts.

**Classifying an original float datum** (what the 1999 source used):

- References from multiple TUs, all in literal shape → the merged literal pool entry for that value. Source uses plain literals.
- Any load+push, load+store, `fld`+`fchs`, const-first `fmul`/`fadd`, or a second same-value datum elsewhere → a NAMED constant of the owning TU (`static const LegoFloat` at file scope; `extern const` only if other TUs reference the same address). Multiple named constants may hold the same value — even within one TU.
- Only `fcom`/`fld`-shaped single-TU references → ambiguous; prefer the literal unless a match proves otherwise.
- **`x += c` is a shape oracle:** `fld [x]; fadd [c]` (value-first) ⇒ literal; `fld [c]; fadd [x]` (const-first) ⇒ named. Same for commutative `fmul`: const as the memory operand ⇒ literal; const loaded first ⇒ named.
- A single-TU-referenced datum can still be that value's literal pool if every other user of the value compiles to immediates (`mov [dst], imm32` stores never reference the pool) — check the shapes, not just the spread.

**reccmp rules.** Operands compare by rendered entity name. Literal pool entries are auto-discovered on BOTH sides (FPU-referenced addresses in read-only sections) and render as the value (`0.5 (FLOAT)`), so literal↔literal matches with no configuration. `reccmp/lego-racers-floats.csv` seeds orig-side FLOAT entities where auto-discovery fails (non-FPU references such as double push-pairs; writable sections). A GLOBAL annotation and a floats-CSV row on the SAME address is always wrong — it renders `(DATA)` vs `(FLOAT)` and permanently mismatches every reference.

**Policy.** Literal in source ⇔ CSV row (or auto-discovery), no annotation. Named constant in source ⇔ GLOBAL annotation, no CSV row, and the name used at every original reference site.

## Naming Members from Matched Code

A member name is proven when a `// FUNCTION:` match forces a specific semantic interpretation — e.g. a member that is both `count++` inside a loop bounded at 20 AND stored into `g_fileSourceCount` is unambiguously a file-source count. Rename the `m_unk0xNN` placeholder once a match corroborates usage. Member *types* still follow the `undefined`/`undefined4` rule.

## Naming Functions from Matched Code

Rename from `VTable0xNN` / `FUN_XXXXXXXX` to a semantic name when evidence is strong:

- **Clear pair with a named counterpart.** `VTable0x20` calls `m_input.Shutdown()`; adjacent `VTable0x1c` calls the input-init helper with hInstance/hWnd → `VTable0x1c` is `InitializeInput`.
- **Symmetric with a named method.** `VTable0x10` undoes every action `Initialize()` took and is also `~Class()` body → `Destroy`.
- **Body leaves no interpretation.** A one-line tail call to `InitInput`, or a loop opening every line of a newline list and publishing them as globals.

Do not rename on weak evidence. If multiple plausible names exist (`OpenFileSources` vs. `LoadFileSources` vs. `RegisterFileSources`), keep `FUN_XXXXXXXX`. A misleading name is worse than a neutral placeholder. Renaming a virtual does not affect codegen — the vtable is slot-indexed — so it's safe if all call sites and overrides are updated together.

**Lifecycle vocabulary.** Match existing class method names so the whole codebase shares one vocabulary:

- `Initialize()` — explicit init separate from the ctor (ctor zeroes fields, `Initialize` allocates/loads/registers).
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
