
---

# 📌 **Google Benchmark CLI Parameters**
_(Quick reference for running benchmarks)_

When running a **Google Benchmark executable**, you can pass various parameters to control output, repetitions, filtering, and more.

---

## 📂 **1. Specifying Output File & Format**
Google Benchmark allows exporting results to a file in either **JSON** or **CSV** format.

### **JSON Output (Default)**
```sh
./benchmark_executable --benchmark_out=results.json --benchmark_out_format=json
```

### **CSV Output**
```sh
./benchmark_executable --benchmark_out=results.csv --benchmark_out_format=csv
```

| **Flag**                | **Description**                                       | **Example** |
|-------------------------|-------------------------------------------------------|-------------|
| `--benchmark_out=<file>` | Saves benchmark results to the specified file.       | `results.json` |
| `--benchmark_out_format=<format>` | Output format: `json` (default) or `csv`.  | `json`, `csv` |

---

## 🎯 **2. Filtering Specific Benchmarks**
To run only **benchmarks matching a pattern**, use:

```sh
./benchmark_executable --benchmark_filter=RegexPattern
```

🔹 **Example: Run only benchmarks with "Fast" in the name**
```sh
./benchmark_executable --benchmark_filter=Fast.*
```

🔹 **Example: Run all benchmarks except those with "Slow" in the name**
```sh
./benchmark_executable --benchmark_filter=^(?!.*Slow).*
```

---

## 🔄 **3. Controlling Repetitions & Iterations**
You can control the number of times a benchmark runs.

| **Flag**                     | **Description**                                      | **Example** |
|------------------------------|------------------------------------------------------|-------------|
| `--benchmark_repetitions=N`   | Runs each benchmark N times.                        | `--benchmark_repetitions=5` |
| `--benchmark_min_time=T`      | Ensures each benchmark runs for at least T seconds. | `--benchmark_min_time=2.0` |
| `--benchmark_iterations=N`    | Manually set the number of iterations.              | `--benchmark_iterations=1000` |

🔹 **Example: Run each benchmark 5 times with a minimum runtime of 2 seconds**
```sh
./benchmark_executable --benchmark_repetitions=5 --benchmark_min_time=2.0
```

---

## 🚀 **4. Controlling Benchmark Display**
Google Benchmark provides options to **adjust the output format**.

| **Flag**                     | **Description**                                  | **Example** |
|------------------------------|--------------------------------------------------|-------------|
| `--benchmark_format=console`  | Default format for human-readable output.       | `console` (default) |
| `--benchmark_format=json`     | Prints results as a JSON object.                | `json` |
| `--benchmark_format=csv`      | Prints results in CSV format.                   | `csv` |

🔹 **Example: Print results as JSON to the console**
```sh
./benchmark_executable --benchmark_format=json
```

---

## 🛠 **5. CPU and Thread Control**
Google Benchmark allows controlling the number of **threads** and **CPU scaling**.

| **Flag**                   | **Description**                                    | **Example** |
|----------------------------|----------------------------------------------------|-------------|
| `--benchmark_threads=N`    | Runs benchmarks using N threads.                  | `--benchmark_threads=4` |
| `--benchmark_counters_tabular=true` | Displays counters in tabular form.       | `true` |

🔹 **Example: Run benchmarks using 8 threads**
```sh
./benchmark_executable --benchmark_threads=8
```

---

## 📊 **6. Handling CPU Frequency Scaling**
To **disable CPU frequency scaling** (recommended for accurate results):

```sh
./benchmark_executable --benchmark_enable_random_interleaving=true
```

---

## ✅ **7. Running Benchmarks with Environment Variables**
You can also **control benchmarks via environment variables** instead of CLI flags.

| **Environment Variable**       | **Description**                           | **Example** |
|--------------------------------|-------------------------------------------|-------------|
| `BENCHMARK_OUT`               | Equivalent to `--benchmark_out`.          | `results.json` |
| `BENCHMARK_OUT_FORMAT`        | Equivalent to `--benchmark_out_format`.   | `json`, `csv` |
| `BENCHMARK_REPETITIONS`       | Equivalent to `--benchmark_repetitions`.  | `5` |

🔹 **Example: Run a benchmark and save results to JSON using environment variables**
```sh
export BENCHMARK_OUT=results.json
export BENCHMARK_OUT_FORMAT=json
./benchmark_executable
```

---
