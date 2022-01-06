echo "Running the benchmark on the hotpath."
cmake -S . -DBENCHMARK_HOTPATH:BOOL=True -DENABLE_CPP_BENCHMARKS:BOOL=False \
-B build
cmake --build build
cmake --install build
./bin/benchmarker
echo "DONE"