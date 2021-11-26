project(benchmarking)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(lib/benchmark)
include_directories(lib/benchmark/include)
include_directories(../src/)
set(SOURCE_FILES benchmarking.cpp ../src/bollingerBand/BollingerBand.cpp)

add_executable(benchmarking ${SOURCE_FILES})
target_link_libraries(benchmarking
        benchmark::benchmark -lpthread
        bollingerBand
        dataManager
        exchange
        ordering-system
)

install(TARGETS benchmarking DESTINATION bin)


