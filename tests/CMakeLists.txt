include(CTest)
find_package(Catch2 3 REQUIRED)
include(Catch)

function(add_test_executable TARGET_NAME SRC_FILES)
    target_add_executable(${TARGET_NAME} ${SRC_FILES})
    target_link_libraries(${TARGET_NAME} PRIVATE Catch2::Catch2WithMain)
    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_20)
    catch_discover_tests(${TARGET_NAME})
endfunction()

add_test_executable(example_test example_test.cpp TestTypes.hpp)