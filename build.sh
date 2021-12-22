mkdir build || true
git pull --recurse-submodules
cmake -S . -DBENCHMARK_HOTPATH:BOOL=False\
-DENABLE_CPP_BENCHMARKS:BOOL=False -B build
cmake --build build
cmake --install build
