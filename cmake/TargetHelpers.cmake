# TargetHelpers.cmake
# Convenient wrappers around add_executable and add_library that automatically
# apply compiler settings based on cache variables.
#
# Cache Variables (set via CMakePresets.json):
#   ENABLE_COMPILER_WARNINGS (default: ON)
#   TREAT_WARNINGS_AS_ERRORS (default: OFF for dev, ON for release)
#   ENABLE_SANITIZER_ADDRESS (default: OFF)
#   ENABLE_SANITIZER_THREAD (default: OFF)
#   ENABLE_SANITIZER_UNDEFINED (default: OFF)
#   ENABLE_LTO (default: OFF for dev, ON for release)
#
# Usage:
#   target_add_executable(my_app src/main.cpp src/util.cpp)
#   target_add_library(my_lib src/lib.cpp src/helper.cpp)

include(CompilerSettings)

function(target_add_executable target_name)
    add_executable(${target_name} ${ARGN})

    # Apply compiler warnings if enabled
    if(ENABLE_COMPILER_WARNINGS)
        apply_compiler_warnings(${target_name})
    endif()

    # Treat warnings as errors if enabled
    if(TREAT_WARNINGS_AS_ERRORS)
        apply_error_on_warnings(${target_name})
    endif()

    # Apply sanitizers if enabled (usually only one at a time)
    if(ENABLE_SANITIZER_ADDRESS)
        apply_sanitizer(${target_name} address)
    endif()

    if(ENABLE_SANITIZER_THREAD)
        apply_sanitizer(${target_name} thread)
    endif()

    if(ENABLE_SANITIZER_UNDEFINED)
        apply_sanitizer(${target_name} undefined)
    endif()

    # Apply LTO if enabled
    if(ENABLE_LTO)
        apply_lto(${target_name})
    endif()
endfunction()

function(target_add_library target_name)
    # Determine library type (default to STATIC if not specified)
    # Check if first argument after target name is SHARED/STATIC/INTERFACE
    set(lib_type "STATIC")
    set(sources ${ARGN})

    if(ARGN MATCHES "^(SHARED|STATIC|OBJECT|INTERFACE|MODULE|UNKNOWN)")
        list(GET ARGN 0 lib_type)
        list(REMOVE_AT sources 0)
    endif()

    add_library(${target_name} ${lib_type} ${sources})

    # Skip compiler settings for INTERFACE libraries (header-only)
    if(NOT lib_type STREQUAL "INTERFACE")
        # Apply compiler warnings if enabled
        if(ENABLE_COMPILER_WARNINGS)
            apply_compiler_warnings(${target_name})
        endif()

        # Treat warnings as errors if enabled
        if(TREAT_WARNINGS_AS_ERRORS)
            apply_error_on_warnings(${target_name})
        endif()

        # Apply sanitizers if enabled
        if(ENABLE_SANITIZER_ADDRESS)
            apply_sanitizer(${target_name} address)
        endif()

        if(ENABLE_SANITIZER_THREAD)
            apply_sanitizer(${target_name} thread)
        endif()

        if(ENABLE_SANITIZER_UNDEFINED)
            apply_sanitizer(${target_name} undefined)
        endif()

        # Apply LTO if enabled
        if(ENABLE_LTO)
            apply_lto(${target_name})
        endif()
    endif()
endfunction()
