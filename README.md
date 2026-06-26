[![CI](https://github.com/chrisi5700/cmake_start/actions/workflows/ci.yaml/badge.svg)](https://github.com/chrisi5700/cmake_start/actions/workflows/ci.yaml)

# CMake Starter Template

A structured, modern **C++23** project template built around **CMake presets** and **vcpkg**.
It ships with benchmarking, unit testing, static analysis, sanitizers, and a dedicated playground
for experimentation.

---

## Features

- **CMake preset-based workflow** (`dev`, `llm`, `release`, each with a vcpkg variant)
- **vcpkg** manifest-mode dependency management
- **Static analysis & sanitizers** — clang-tidy, cppcheck, ASan/UBSan, warnings-as-errors (see the `llm` preset)
- **Catch2** for unit testing
- **Google Benchmark** for performance analysis
- **Playground** for isolated prototyping
- **libs/** for external or custom libraries

---

## Building the Project

Dependencies are resolved through vcpkg, so configure with one of the provided presets
(set `VCPKG_ROOT` to your vcpkg checkout first):

```sh
# Configure (Debug, sanitizers, static analysis)
cmake --preset dev-vcpkg

# Build all targets
cmake --build --preset dev-vcpkg

# Run tests
ctest --test-dir build/dev-vcpkg --output-on-failure

# Run benchmarks
./build/dev-vcpkg/bench/bench
```

Available configure presets: `dev-vcpkg`, `llm-vcpkg`, `release-vcpkg` (plus `dev-vcpkg-msvc` for
Visual Studio).

---

## Project Structure & Extension Guide

### Defining targets — top-level `CMakeLists.txt`

Libraries and executables are declared directly in the top-level `CMakeLists.txt` with the
`target_add_library` / `target_add_executable` helpers (defined in `cmake/TargetHelpers.cmake`),
which automatically apply the configured warnings, sanitizers, and analysis tools. Put
implementation files under `src/` and public headers under `include/`.

#### Basic Library Definition

```cmake
target_add_library(my_lib src/my_lib.cpp)

target_include_directories(my_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>  # During build
    $<INSTALL_INTERFACE:include>                    # After installation
)

target_compile_features(my_lib PUBLIC cxx_std_23)
```

**Key Concepts:**

- **BUILD_INTERFACE**: include paths used when building the project itself
- **INSTALL_INTERFACE**: include paths used by external projects after installation
- **PRIVATE/PUBLIC/INTERFACE**: controls visibility of properties to consuming targets

#### Header-Only Library

For libraries with only headers (templates, inline functions) — this is exactly how the bundled
`logger` target is defined:

```cmake
target_add_library(my_header_lib INTERFACE)

target_include_directories(my_header_lib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(my_header_lib INTERFACE cxx_std_23)
```

#### Setting the C++ Standard

The standard is set once for all presets via the `base` preset in `CMakePresets.json`:

```json
  "CMAKE_CXX_STANDARD": "23"
```

### `/tests` - Unit Tests

Register a test executable in `tests/CMakeLists.txt` with the `add_test_executable` helper, then
write tests using **Catch2**:

```cpp
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Addition works") {
    REQUIRE(2 + 2 == 4);
}
```

Run them:

```sh
ctest --test-dir build/dev-vcpkg --output-on-failure
```

### `/bench` - Benchmarks

Use **Google Benchmark** for performance analysis:

```cpp
#include <benchmark/benchmark.h>

static void BM_MyFunction(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(MyFunction());
    }
}

BENCHMARK(BM_MyFunction)->Range(8, 8<<10);
```

### `/playground` - Experimentation

Use the `playground/` directory for quick testing and prototyping:

```cpp
#include <print>

int main() {
    std::println("Quick test here");
}
```

Build and run:

```sh
cmake --build --preset dev-vcpkg
./build/dev-vcpkg/playground/playground
```
