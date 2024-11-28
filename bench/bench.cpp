//
// Created by chris on 17.10.24.
//

#include <benchmark/benchmark.h>
#include <vector>
#include <numeric>

// A function to sum elements in a vector
int sumVector(const std::vector<int>& v) {
    return std::accumulate(v.begin(), v.end(), 0);
}

// Benchmark for summing a vector
static void BM_SumVector(benchmark::State& state) {
    // Create a vector with the size provided by the benchmark state
    std::vector<int> v(state.range(0), 1); // Vector of 1's of size range(0)

    // Loop over each state iteration (measures performance over multiple runs)
    for (auto _ : state) {
        benchmark::DoNotOptimize(sumVector(v)); // Perform the sum and prevent optimization
    }

    // Set the number of processed elements for more meaningful stats
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

// Register the function as a benchmark and set a range of input sizes
BENCHMARK(BM_SumVector)->Range(8, 8<<10); // Benchmark on input sizes from 8 to 8192

// Main function to run the benchmarks
BENCHMARK_MAIN();
