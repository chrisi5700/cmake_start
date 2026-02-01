include(CTest)
find_package(Catch2 3 REQUIRED)
include(Catch)

function(add_test_executable TARGET_NAME SRC_FILES)
    target_add_executable(${TARGET_NAME} ${SRC_FILES})
    target_link_libraries(${TARGET_NAME} PRIVATE Catch2::Catch2WithMain)
    catch_discover_tests(${TARGET_NAME} DISCOVERY_MODE POST_BUILD)
endfunction()

add_test_executable(example_test example_test.cpp TestTypes.hpp)
target_link_libraries(example_test PRIVATE test_lib)