# Darwin EES — Phase 1

C++17 ecosystem evolution simulator using deterministic logical ticks, configurable random seeds, probabilistic hunting, inherited traits with mutation, smart-pointer ownership, CMake, and incremental CSV statistics.

## Requirements
- CMake 3.16+
- C++17 compiler (GCC, Clang, or MSVC)
- No third-party libraries

## Build (Linux/macOS)
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build --output-on-failure
```

## Build (Windows PowerShell)
Install Visual Studio Build Tools with the C++ workload and CMake, then run:
```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

## Run
Linux/macOS:
```bash
./build/darwin_ees --ticks 10000 --seed 42 --stats-interval 20 --output output/ecosystem_stats.csv
```
Windows:
```powershell
New-Item -ItemType Directory -Force output
.\build\Release\darwin_ees.exe --ticks 10000 --seed 42 --stats-interval 20 --output output/ecosystem_stats.csv
```
Options: `--world-size` (100), `--water` (15), `--food` (35), `--herbivores` (50), `--predators` (8), `--ticks` (10000), `--seed` (42), `--stats-interval` (20), `--output` (ecosystem_stats.csv), `--help`.

CSV columns include tick, populations, and mean attraction, vision, speed, size, and metabolism for both species. The output is flushed incrementally. Seeded runs are reproducible within the same compiler/runtime implementation.

## Layout
- `include/darwin/`: public headers and configuration
- `src/`: simulation engine and CLI
- `tests/`: lightweight CTest checks

Population coexistence is not mathematically guaranteed: results depend on seed, starting populations, resource density, and ecological parameters.
