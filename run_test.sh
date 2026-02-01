#!/bin/bash
set -e

# Usage: ./run_test_coverage.sh <build_dir> <test_target>
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

echo ""
echo "=== Capturing coverage data ==="
lcov --capture --directory "$BUILD_DIR" \
    --output-file "$BUILD_DIR/coverage.info" \
    --ignore-errors inconsistent \
    --quiet

echo ""
echo "=== Filtering coverage data ==="
lcov --remove "$BUILD_DIR/coverage.info" \
    '/usr/*' \
    '*/tests/*' \
    '*/build/*' \
    --output-file "$BUILD_DIR/coverage_filtered.info" --quiet

echo ""
echo "=== Coverage Summary ==="
lcov --summary "$BUILD_DIR/coverage_filtered.info"