# Add library definitions here
# See README.md for CMake library patterns and examples


target_add_library(test_lib)
target_sources(test_lib PRIVATE div.cpp)
target_include_directories(test_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)