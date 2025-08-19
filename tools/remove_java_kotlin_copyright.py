#!/usr/bin/env python3
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

COMMENT_BLOCK_RE = re.compile(r"^\s*/\*([\s\S]*?)\*/\s*", re.MULTILINE)
LINE_COMMENT_BLOCK_RE = re.compile(r"^(?:\s*//.*\n)+", re.MULTILINE)


def remove_leading_license(text: str) -> str:
    original = text

    def strip_block(t: str) -> str:
        m = COMMENT_BLOCK_RE.match(t)
        if m and re.search(r"copyright", m.group(1), re.IGNORECASE):
            return t[m.end():]
        return t

    def strip_line_block(t: str) -> str:
        m = LINE_COMMENT_BLOCK_RE.match(t)
        if m and re.search(r"copyright", m.group(0), re.IGNORECASE):
            return t[m.end():]
        return t

    # Try to strip at most once per style, from the very top
    text = strip_block(text)
    text = strip_line_block(text)

    # Remove extra leading blank lines
    text = re.sub(r"^\s*\n+", "", text)

    return text if text != original else original


def is_target_file(p: Path) -> bool:
    return p.suffix in {".java", ".kt"}


def main() -> None:
    modified = []
    for path in ROOT.rglob("*"):
        if not path.is_file():
            continue
        # skip common generated/build dirs
        if any(part in {".git", "build", ".gradle", ".idea", ".cxx"} for part in path.parts):
            continue
        if not is_target_file(path):
            continue
        try:
            content = path.read_text(encoding="utf-8", errors="ignore")
        except Exception:
            continue
        new_content = remove_leading_license(content)
        if new_content != content:
            path.write_text(new_content, encoding="utf-8")
            modified.append(str(path.relative_to(ROOT)))
            print(f"Modified: {path}")

    print(f"\nTotal modified: {len(modified)}")
    if modified:
        print("First few modified files:")
        for p in modified[:10]:
            print(" -", p)


if __name__ == "__main__":
    main()





