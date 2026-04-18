import argparse
import logging
from reccmp.compare import Compare
from reccmp.parser import DecompCodebase
from reccmp.parser.node import ParserFunction
from reccmp.project.detect import (
    RecCmpProjectException,
    argparse_add_project_target_args,
    argparse_parse_project_target,
)

# Ignore all compare-db messages.
logging.getLogger("reccmp.compare").addHandler(logging.NullHandler())

logger = logging.getLogger()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="folded")
    argparse_add_project_target_args(parser)
    return parser.parse_args()


def main():
    args = parse_args()
    try:
        target = argparse_parse_project_target(args=args)
    except RecCmpProjectException as e:
        logger.error(e.args[0])
        return 1

    print(f"Checking identical code folding in: {target.target_id}")

    compare = Compare.from_target(target)

    codebase = DecompCodebase(compare.code_files, compare.target_id)
    codebase.prune_invalid_addrs(compare.orig_bin.is_valid_vaddr)
    codebase.prune_reused_addrs()

    # Combine annotations for folded functions on the same address.
    functions: dict[int, list[ParserFunction]] = {}
    for fun in codebase.iter_line_functions():
        functions.setdefault(fun.offset, []).append(fun)

    for fun in codebase.iter_name_functions():
        functions.setdefault(fun.offset, []).append(fun)

    failed = False

    for addr, fs in functions.items():
        all_folded = all(f.is_folded for f in fs)
        none_folded = all(not f.is_folded for f in fs)
        if not all_folded and not none_folded:
            failed = True
            print(f"{addr:#8x}: Some annotations are folded, some not.")

    folds = {key: [f for f in value if f.is_folded] for key, value in functions.items()}

    for addr, folded in folds.items():
        if not folded:
            continue

        # pylint: disable=protected-access
        matches = [
            compare._lines_db.find_function(
                fun.filename, fun.line_number, fun.end_line, folded=True
            )
            for fun in folded
            if fun.filename is not None
        ]

        # Filter out None
        matched_count = len([m for m in matches if m])

        if matched_count == 0:
            failed = True
            print(f"{addr:#8x}: No match for folded annotation.")

        if matched_count > 1:
            failed = True
            print(f"{addr:#8x}: Matched {matched_count} recomp functions.")

    return failed


if __name__ == "__main__":
    raise SystemExit(main())
