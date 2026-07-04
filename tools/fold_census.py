#!/usr/bin/env python3
"""Census of standalone trivial-body functions in a PE .text section.

The original binaries fold byte-identical trivial bodies in two separate pools:
methods defined in the class body (SELECT_ANY COMDATs) fold only with each
other, and out-of-line /Gy functions fold only with each other - so the same
bytes coexist at two addresses (e.g. `xor eax,eax; ret 0xc` at both 0x466090
and 0x473490 in LEGORacers.exe). Matching the original means defining each
function on its original side of that boundary (see CLAUDE.md). This tool lists, per
trivial byte pattern, every 16-aligned standalone occurrence (padding before
and after), so the recompiled binary's fold landscape can be compared against
the original's.

Usage:
  python3 tools/fold_census.py <binary> [<binary2>]

With two binaries, prints the census side by side (original first).
"""

import sys

import pefile

PATTERNS = {
    "ret": bytes([0xC3]),
    "ret4": bytes([0xC2, 0x04, 0x00]),
    "ret8": bytes([0xC2, 0x08, 0x00]),
    "ret0c": bytes([0xC2, 0x0C, 0x00]),
    "xor;ret": bytes([0x33, 0xC0, 0xC3]),
    "xor;ret4": bytes([0x33, 0xC0, 0xC2, 0x04, 0x00]),
    "xor;ret8": bytes([0x33, 0xC0, 0xC2, 0x08, 0x00]),
    "xor;ret0c": bytes([0x33, 0xC0, 0xC2, 0x0C, 0x00]),
    "mov1;ret": bytes([0xB8, 0x01, 0x00, 0x00, 0x00, 0xC3]),
    "mov[ecx+c];ret": bytes([0x8B, 0x41, 0x0C, 0xC3]),
}
PADDING = (0x90, 0xCC)


def census(path):
    pe = pefile.PE(path, fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    text = next(s for s in pe.sections if s.Name.rstrip(b"\0") == b".text")
    data = text.get_data()
    lo = base + text.VirtualAddress

    result = {}
    for name, pat in PATTERNS.items():
        addrs = []
        for off in range(16, len(data) - 16, 16):
            if (
                data[off : off + len(pat)] == pat
                and data[off - 1] in PADDING
                and all(b in PADDING for b in data[off + len(pat) : off + 16])
            ):
                addrs.append(lo + off)
        result[name] = addrs
    return result


def main():
    if len(sys.argv) not in (2, 3):
        sys.exit(__doc__)

    censuses = [census(p) for p in sys.argv[1:]]
    for name in PATTERNS:
        for label, c in zip(("orig", "recomp"), censuses):
            addrs = c[name]
            tag = f"{label}: " if len(censuses) == 2 else ""
            print(f"{name:15s} {tag}x{len(addrs):2d}  " + " ".join(hex(a) for a in addrs))


if __name__ == "__main__":
    main()
