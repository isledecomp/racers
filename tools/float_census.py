#!/usr/bin/env python3
"""Classify float constant data in the original binaries.

For every float-plausible dword (and qword) in .rdata/.data, find all code
references and classify the datum:

  POOL    multi-TU reference spread, or single-site pure-FPU use -> a merged
          literal pool entry; source uses a literal; address belongs in the
          floats CSV (LEGORACERS) or is auto-discovered (read-only + FPU ref).
  NAMED   reference fingerprint proves a named constant: the compiler never
          folds named consts, loads them first in fmul/fadd, and emits
          load+push / load+store instead of immediates. Source should declare
          a named const in the owning TU with a GLOBAL annotation, and the
          address must NOT be in the floats CSV.
  DATA    writable section (.data) -> named non-const global; reccmp cannot
          auto-discover it (read-only filter), so it needs a GLOBAL annotation.

Also flags CONFLICTs: addresses present in both the floats CSV and a GLOBAL
annotation (these render FLOAT vs DATA and can never match), and CSV rows
whose fingerprints prove NAMED.

Usage: python3 tools/float_census.py <original-binary> [--csv <floats.csv>]
                                     [--src <dir> ...] [--value <float>]
"""

import argparse
import re
import struct
import sys
from pathlib import Path

import pefile

FPU_FIRST = {0xD8, 0xD9, 0xDC, 0xDD}
# modrm bytes for [disp32] forms of the const-consuming FPU ops (reg field varies)
FPU_MODRM = {0x05, 0x0D, 0x15, 0x1D, 0x25, 0x2D, 0x35, 0x3D}


def classify_ref(img, ref_off):
    """Look backwards from the address-immediate to identify the instruction."""
    # The 4-byte address sits at ref_off. Check preceding opcode bytes.
    b2, b1 = img[ref_off - 2], img[ref_off - 1]
    if b2 in FPU_FIRST and b1 in FPU_MODRM:
        op = (b2, b1)
        if op == (0xD9, 0x05) or op == (0xDD, 0x05):
            return "fld"
        if b1 in (0x15, 0x1D):
            return "fcom"
        return "fpu-arith"  # fadd/fmul/fsub/fdiv on memory operand (const-second)
    if b2 == 0x8B or b2 == 0xA1:  # mov r32, [disp32]
        return "load"
    if b2 == 0xFF and b1 == 0x35:
        return "push-mem"
    return "other"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("binary")
    ap.add_argument("--csv", type=Path)
    ap.add_argument("--src", type=Path, nargs="*", default=[])
    ap.add_argument("--value", type=float, default=None)
    ap.add_argument("--all", action="store_true", help="include unreferenced data")
    args = ap.parse_args()

    pe = pefile.PE(args.binary)
    base = pe.OPTIONAL_HEADER.ImageBase
    img = bytes(pe.get_memory_mapped_image())

    text = next(s for s in pe.sections if s.Name.startswith(b".text"))
    tlo, thi = text.VirtualAddress, text.VirtualAddress + text.Misc_VirtualSize

    csv_addrs = set()
    if args.csv and args.csv.exists():
        for line in args.csv.read_text().splitlines():
            m = re.match(r"0x([0-9a-fA-F]+),", line)
            if m:
                csv_addrs.add(int(m.group(1), 16))

    global_addrs = {}
    for src in args.src:
        for f in list(src.rglob("*.cpp")) + list(src.rglob("*.h")):
            txt = f.read_text(errors="replace")
            for m in re.finditer(r"//\s*GLOBAL:\s*\w+\s+0x([0-9a-fA-F]+)", txt):
                global_addrs.setdefault(int(m.group(1), 16), str(f))

    # collect candidate float dwords in data sections
    results = []
    for s in pe.sections:
        nm = s.Name.decode().rstrip("\x00")
        if nm not in (".rdata", ".data"):
            continue
        for i in range(0, s.Misc_VirtualSize - 3, 4):
            off = s.VirtualAddress + i
            raw = img[off : off + 4]
            if len(raw) < 4:
                break
            (v,) = struct.unpack("<f", raw)
            # float-plausible filter: normal magnitude, not denormal/nan/inf
            if v != v or v in (float("inf"), float("-inf")) or v == 0:
                continue
            if not (1e-6 < abs(v) < 1e9):
                continue
            if args.value is not None and abs(v - args.value) > 1e-9 * max(
                1, abs(args.value)
            ):
                continue
            va = base + off
            needle = struct.pack("<I", va)
            refs = []
            j = tlo
            while True:
                j = img.find(needle, j, thi)
                if j < 0:
                    break
                refs.append(j)
                j += 1
            if not refs and not args.all:
                continue
            kinds = [classify_ref(img, r) for r in refs]
            spread = (base + max(refs)) - (base + min(refs)) if refs else 0
            named_evidence = [k for k in kinds if k in ("load", "push-mem")]
            # fld-first heuristic needs context; 'fld' alone is ambiguous
            if nm == ".data":
                cls = "DATA(writable)"
            elif named_evidence:
                cls = "NAMED(load-ref)"
            elif spread > 0x8000 or len(refs) >= 6:
                cls = "POOL(spread)"
            else:
                cls = "AMBIG"
            status = []
            if va in csv_addrs:
                status.append("CSV")
            if va in global_addrs:
                status.append("GLOBAL")
            flag = ""
            if "CSV" in status and "GLOBAL" in status:
                flag = " *** CONFLICT csv+annotation"
            elif cls == "NAMED(load-ref)" and "CSV" in status:
                flag = " *** CSV row but named fingerprint"
            elif cls == "DATA(writable)" and "GLOBAL" not in status and refs:
                flag = " *** writable float w/o GLOBAL annotation"
            results.append(
                (va, v, nm, len(refs), spread, kinds, cls, "+".join(status), flag)
            )

    for va, v, nm, n, spread, kinds, cls, status, flag in results:
        kindstr = ",".join(sorted(set(kinds)))
        print(
            f"{va:#010x} {nm:6} {v:<14.7g} refs={n:<3} spread={spread:<8x} "
            f"[{kindstr}] {cls:16} {status:10}{flag}"
        )


if __name__ == "__main__":
    main()
