project(CPPDesignPatternsforLowLatencyTrading)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(lib/benchmark)
include_directories(lib/benchmark/include)

add_subdirectory(src)


