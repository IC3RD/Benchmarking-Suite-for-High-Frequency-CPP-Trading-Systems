echo "Running the benchmark on individual functions."
cmake -S . -DBENCHMARK_HOTPATH:BOOL=False -DENABLE_CPP_BENCHMARKS:BOOL=True -B build
cmake --build build
cmake --install build
./bin/benchmarker
echo "DONE"