include(CTest)
find_package(Catch2 3 REQUIRED)
include(Catch)



function(add_test_executable TARGET_NAME SRC_FILES)
    # Create the executable
    add_executable(${TARGET_NAME} ${SRC_FILES})


    # Link Catch2 to the executable
    target_link_libraries(${TARGET_NAME} Catch2::Catch2WithMain)

    # Add warning flags based on the compiler
    target_add_warnings(${TARGET_NAME})
    target_add_sanitizer(${TARGET_NAME})
    # Register the test with CTest
    catch_discover_tests(${TARGET_NAME})
endfunction()

add_test_executable(example_test example_test.cpp) # creates a test adds asan, warnings and links with catch2.3 then makes test available