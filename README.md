# CMake Starter Template

This repository provides a structured C++ project template using **CMake** and **Nix flakes**.  
It includes benchmarking, testing, and a dedicated playground for experimentation.

---

## Features

- **CMake-based project structure**
- **Nix flake** for a reproducible development environment
- **Google Benchmark** for performance analysis
- **Catch2** for unit testing
- **Playground** for isolated code testing
- **libs/** for external or custom libraries

---

## Development with Nix

A **Nix flake** provides a consistent development environment.

```sh
nix develop
```

---

## Building the Project

```sh
# Configure the build
cmake -B build -DCMAKE_BUILD_TYPE=Release

# Build all targets
cmake --build build

# Run tests
ctest --test-dir build

# Run benchmarks
./build/bench/bench
```

---

## Project Structure & Extension Guide

### `/src` - Source Libraries

The `src/` directory is where you define CMake libraries for your project. Here are common patterns:

#### Basic Library Definition

```cmake
target_add_library(MyLib src/mylib.cpp src/mylib.hpp)

target_include_directories(MyLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  # During build
    $<INSTALL_INTERFACE:include>                            # After installation
)

target_compile_features(MyLib PUBLIC cxx_std_23)
```

**Key Concepts:**

- **BUILD_INTERFACE**: Include paths used when building the project itself
- **INSTALL_INTERFACE**: Include paths used by external projects after installation
- **PRIVATE/PUBLIC/INTERFACE**: Controls visibility of properties to consuming targets

#### Header-Only Library

For libraries with only headers (templates, inline functions):

```cmake
target_add_library(HeaderOnlyLib INTERFACE)

target_include_directories(HeaderOnlyLib INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(HeaderOnlyLib INTERFACE cxx_std_23)
```

#### Setting C++ Standard

Explicitly set the C++ for all presets you can change this line in ``CMakePresets.json`` for the `base` preset:

```json lines
  "CMAKE_CXX_STANDARD": "23" -> "20" 
```


### `/tests` - Unit Tests

Write tests in the `tests/` directory using **Catch2**:

```cpp
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Addition works") {
    REQUIRE(2 + 2 == 4);
}
```

Run tests:

```sh
ctest --test-dir build
```

See `tests/TestTypes.hpp` for advanced testing utilities for validating C++ semantics.

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

Compile and run:

```sh
cmake --build build
./build/playground/playground
```
