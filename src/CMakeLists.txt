


# Library example
# add_library(main file.cpp ../include/LibName/file.hpp)
# target_include_directories(main PUBLIC  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
#                                         $<INSTALL_INTERFACE:include>) # fancy but just to make it folder structure independent
#         $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR} is basically just the location of the top level CMake file
# target_compile_features(main PUBLIC cxx_std_23) # set cmake standard for the target

# since ../include is an include directory you can refer to the headers there directly when implementing them

# Users of a library can then include it like #include <LibName/file.hpp>

# Note that this doesnt mean the library is ready to be installed I havent added that because I rarely ever need it
# When just playing around I prefer to add it later on. Theres docs for that online