cmake_minimum_required(VERSION 3.28)
project(test_project)


function(target_add_warnings)
    # First argument is the target.
    set(target ${ARGV0})
    # If only one argument is provided, default to PRIVATE.
    if(ARGC EQUAL 1)
        set(visibility PRIVATE)
    else()
        set(visibility ${ARGV1})
    endif()

    if(MSVC)
        # MSVC warning options
        target_compile_options(${target} ${visibility} /W4 /WX)
    else()
        # GCC/Clang warning options
        target_compile_options(${target} ${visibility}
                -Wall        # Enable all common warnings
                -Wextra      # Enable extra warnings
                -Wpedantic   # Enable strict ISO compliance warnings
                -Werror      # Treat all warnings as errors
        )
    endif()
endfunction()


function(target_add_sanitizer target)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # Enable address sanitizer for GCC/Clang
        target_compile_options(${target} PRIVATE -fsanitize=address)
        target_link_options(${target} PRIVATE -fsanitize=address)
    else()
        message(WARNING "Sanitizer options are not supported for compiler '${CMAKE_CXX_COMPILER_ID}'.")
    endif()
endfunction()



add_subdirectory(src)
add_subdirectory(playground)
add_subdirectory(bench)
add_subdirectory(tests)
# add_subdirectory(libs/SFML) # for example to add other cmake dependencies