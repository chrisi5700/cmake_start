# Add library definitions here
# See README.md for CMake library patterns and examples
find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
target_add_library(logger ${CMAKE_SOURCE_DIR}/include/Logger.hpp)
set_target_properties(logger PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(logger INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(logger INTERFACE spdlog::spdlog fmt::fmt)
target_compile_definitions(logger INTERFACE "logging.txt")
target_compile_features(logger INTERFACE CXX_STD_23)


target_add_library(test_lib)
target_sources(test_lib PRIVATE div.cpp)
target_include_directories(test_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)


