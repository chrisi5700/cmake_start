cmake_minimum_required(VERSION 3.28)
project(test_project)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF) # Causes errors with clang-tidy when used with gcc builds.

# Include CMake modules for target helpers and compiler settings
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(TargetHelpers)

# Default cache variables (can be overridden by CMakePresets.json or command line)
set(ENABLE_COMPILER_WARNINGS ON CACHE BOOL "Enable compiler warnings")
set(TREAT_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat warnings as errors")
set(ENABLE_SANITIZER_ADDRESS OFF CACHE BOOL "Enable AddressSanitizer")
set(ENABLE_SANITIZER_THREAD OFF CACHE BOOL "Enable ThreadSanitizer")
set(ENABLE_SANITIZER_UNDEFINED OFF CACHE BOOL "Enable UndefinedBehaviorSanitizer")
set(ENABLE_LTO OFF CACHE BOOL "Enable Link Time Optimization")
set(ENABLE_CLANG_TIDY OFF CACHE BOOL "Enable clang-tidy static analysis")
set(CLANG_TIDY_WARNINGS_AS_ERRORS OFF CACHE BOOL "Treat clang-tidy warnings as errors")
set(ENABLE_CPPCHECK OFF CACHE BOOL "Enable cppcheck static analysis")
set(ENABLE_COVERAGE OFF CACHE BOOL "Enable code coverage instrumentation")
set(STRICT_MODE OFF CACHE BOOL "Enable all checks and treat everything as errors")
set(ENABLE_CCACHE OFF CACHE BOOL "Enable ccache for faster rebuilds")

add_subdirectory(src)
add_subdirectory(playground)
add_subdirectory(bench)
add_subdirectory(tests)

# add_subdirectory(libs/SFML) # for example to add other cmake dependencies