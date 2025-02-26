


add_executable(playground main.cpp)
target_add_warnings(playground)                         # Function to add warnings
target_add_sanitizer(playground)                        # Function to add asan   both defined in top level cmake file
target_compile_features(playground PRIVATE cxx_std_23)  # Set standard to C++23
# target_compile_definitions(playground PRIVATE L1_CACHE_SIZE=${L1CacheSize}) maybe add some compile definitions too