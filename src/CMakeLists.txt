###############################################
#                CMake Example                #
#       ╭━━━━━━━━━━━━━━━━━━━━━━━━━━╮          #
#       ┃   Adding a Library       ┃          #
#       ╰━━━━━━━━━━━━━━━━━━━━━━━━━━╯          #
###############################################

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃ Basic Library Definition                          ┃
# ┃--------------------------------------------------┃
# ┃ This example shows how to properly define a CMake┃
# ┃ library while keeping paths flexible.            ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛

# Example: Adding a library with source and header files
# add_library(MainLib file.cpp  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>/file.cpp)

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃         Setting Include Directories         ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
# We use two interface types:
#
# - BUILD_INTERFACE: Used when building the project.
#   This ensures we can access headers within the source directory.
#
# - INSTALL_INTERFACE: Used when the library is installed.
#   This keeps paths independent, allowing external projects to use the installed headers.

# Example:
# target_include_directories(MainLib PUBLIC
#     $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>  # During build
#     $<INSTALL_INTERFACE:include>                    # After installation
# )

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃         Setting C++ Standard         ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
# Specify C++23 as the standard for this target:
# target_compile_features(MainLib PUBLIC cxx_std_23)

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃          Header Access in Implementation     ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
# Since `${CMAKE_SOURCE_DIR}/include` is set as an include directory,
# you can directly reference headers inside it without needing a relative path.
#
# Example Usage in Code:
#
#     #include <LibName/file.hpp>
#

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃            Library Installation              ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
# Note: This example does NOT include an installation setup.
# Installation steps can be added later if needed.
# Refer to CMake documentation for `install(TARGETS ...)` usage.

# ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
# ┃       Header-Only Library Example   ┃
# ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
# To create a header-only library, use `INTERFACE`.
# This ensures no compiled object files are created, only header access.

#
# add_library(L1List INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>/header.hpp)

# target_include_directories(L1List INTERFACE
#     $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>  # During build
#     $<INSTALL_INTERFACE:include>                      # After install
# )

# This allows including headers like:
#     #include <L1List.hpp>
