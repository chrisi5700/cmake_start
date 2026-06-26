#!/bin/bash
set -e

# Always run from the repo root so the relative defaults below resolve.
cd "$(dirname "$0")/.."

# Usage: ./scripts/run_test.sh <build_dir> <test_target>
BUILD_DIR="${1:-build/dev-vcpkg}"
TEST_TARGET="${2:-example_test}"

echo "=== Building test target: $TEST_TARGET ==="
cmake --build "$BUILD_DIR" --target "$TEST_TARGET"

echo ""
echo "=== Zeroing coverage counters ==="
lcov --zerocounters --directory "$BUILD_DIR" --quiet

echo ""
echo "=== Running test: $TEST_TARGET ==="
"$BUILD_DIR/tests/$TEST_TARGET"

# `empty`/`unused` are tolerated so the template still passes before any
# production code (and thus any coverage data) exists.
echo ""
echo "=== Capturing coverage data ==="
lcov --capture --directory "$BUILD_DIR" \
    --output-file "$BUILD_DIR/coverage.info" \
    --ignore-errors inconsistent,empty \
    --quiet

echo ""
echo "=== Filtering coverage data ==="
lcov --remove "$BUILD_DIR/coverage.info" \
    '/usr/*' \
    '*/tests/*' \
    '*/build/*' \
    --output-file "$BUILD_DIR/coverage_filtered.info" \
    --ignore-errors empty,unused --quiet

echo ""
echo "=== Coverage Summary ==="
lcov --summary "$BUILD_DIR/coverage_filtered.info" --ignore-errors empty