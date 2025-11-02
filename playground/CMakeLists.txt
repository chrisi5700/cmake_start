
target_add_executable(playground main.cpp)
target_compile_features(playground PRIVATE cxx_std_23)
# target_compile_definitions(playground PRIVATE SOME_DEFINE=VALUE)