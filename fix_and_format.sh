#!/bin/bash
set -e

BUILD_DIR="${1:-build/dev-vcpkg}"
TARGET="${2:-src}"

echo "==================================="
echo "  Auto-fix and Format Code (Fast)"
echo "==================================="

# 1. Format code
echo ""
echo "[1/2] Running clang-format..."
find "$TARGET" \( -name "*.cpp" -o -name "*.hpp" -o -name "*.h" \) \
    -not -path "*/build/*" \
    -not -path "*/vcpkg_installed/*" \
    -exec clang-format -i {} \;

# 2. Apply clang-tidy fixes in parallel
echo ""
echo "[2/2] Running clang-tidy --fix (parallel)..."

# Find run-clang-tidy script (comes with clang-tidy)
RUN_CLANG_TIDY=$(which run-clang-tidy || which run-clang-tidy.py || echo "")

if [ -n "$RUN_CLANG_TIDY" ]; then
    $RUN_CLANG_TIDY \
        -p="$BUILD_DIR" \
        -fix \
        -header-filter='' \
        -j $(nproc) \
        "$TARGET"
else
    # Fallback to serial execution
    find "$TARGET" \( -name "*.cpp" -o -name "*.hpp" \) \
        -not -path "*/build/*" \
        -not -path "*/vcpkg_installed/*" | \
        while read -r file; do
            clang-tidy --fix --fix-errors --header-filter='' -p="$BUILD_DIR" "$file" 2>/dev/null || true
        done
fi

echo ""
echo "✓ Done!"