project(benchmarking)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(lib/benchmark)
include_directories(lib/benchmark/include)
#include_directories(../src/)
set(SOURCE_FILES benchmarking.cpp)

add_executable(benchmarking ${SOURCE_FILES})
target_link_libraries(benchmarking
        benchmark::benchmark -lpthread
        dataManager
        ordering-system
        tradingStrategies
        )

install(TARGETS benchmarking DESTINATION bin)


