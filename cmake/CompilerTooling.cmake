# CompilerTooling.cmake
# Static analysis, coverage, and build optimization tools

# Apply clang-tidy to a target
function(apply_clang_tidy target_name)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)

    if(NOT CLANG_TIDY_EXE)
        if(STRICT_MODE)
            message(FATAL_ERROR "STRICT_MODE enabled but clang-tidy not found!")
        else()
            message(WARNING "clang-tidy requested but not found")
            return()
        endif()
    endif()

    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")

    # Add warnings-as-errors flag if enabled
    if(CLANG_TIDY_WARNINGS_AS_ERRORS OR STRICT_MODE)
        list(APPEND CLANG_TIDY_COMMAND "--warnings-as-errors=*")
    endif()


    # Optional: Add specific checks or config file
    # list(APPEND CLANG_TIDY_COMMAND "--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")

    set_target_properties(${target_name} PROPERTIES
            CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}"
    )

    message(STATUS "clang-tidy enabled for ${target_name}")
endfunction()

# Apply cppcheck to a target
function(apply_cppcheck target_name)
    find_program(CPPCHECK_EXE NAMES cppcheck)

    if(NOT CPPCHECK_EXE)
        if(STRICT_MODE)
            message(FATAL_ERROR "STRICT_MODE enabled but cppcheck not found!")
        else()
            message(WARNING "cppcheck requested but not found")
            return()
        endif()
    endif()

    set(CPPCHECK_COMMAND
            "${CPPCHECK_EXE}"
            "--enable=warning,style,performance,portability"
            "--suppress=missingIncludeSystem"
            "--suppress=knownConditionTrueFalse"  # Tests have known conditions
            "--inline-suppr"
            "--quiet"
    )

    if(STRICT_MODE)
        list(APPEND CPPCHECK_COMMAND "--error-exitcode=1")
    endif()

    set_target_properties(${target_name} PROPERTIES
            CXX_CPPCHECK "${CPPCHECK_COMMAND}"
    )

    message(STATUS "cppcheck enabled for ${target_name}")
endfunction()

# Apply code coverage instrumentation
function(apply_coverage target_name)
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(WARNING "Coverage should typically be used with Debug builds")
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target_name} PRIVATE
                --coverage
                -fno-inline
                -fno-inline-small-functions
                -fno-default-inline
        )
        target_link_options(${target_name} PRIVATE --coverage)
        message(STATUS "Coverage enabled for ${target_name}")
    else()
        message(WARNING "Coverage not supported for compiler ${CMAKE_CXX_COMPILER_ID}")
    endif()
endfunction()

# Enable ccache for faster rebuilds
function(enable_ccache)
    find_program(CCACHE_EXE NAMES ccache sccache)

    if(CCACHE_EXE)
        set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_EXE}" PARENT_SCOPE)
        set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_EXE}" PARENT_SCOPE)
        message(STATUS "Using ${CCACHE_EXE} for compiler caching")
    else()
        if(STRICT_MODE)
            message(FATAL_ERROR "STRICT_MODE enabled but ccache/sccache not found!")
        else()
            message(WARNING "ccache requested but not found")
        endif()
    endif()
endfunction()

