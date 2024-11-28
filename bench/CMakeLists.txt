find_package(benchmark REQUIRED)


add_executable(bench bench.cpp)
target_link_libraries(bench PRIVATE benchmark::benchmark) # using google benchmark for benchmarks..
target_add_warnings(bench)