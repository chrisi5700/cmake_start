


add_executable(playground main.cpp)
target_add_warnings(playground)
target_add_sanitizer(playground)
target_compile_features(playground PRIVATE cxx_std_23)