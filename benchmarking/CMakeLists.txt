project(CPPDesignPatternsforLowLatencyTrading)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(lib/benchmark)
include_directories(lib/benchmark/include)
set(SOURCE_FILES benchmarking.cpp)


add_library(benchmarking ${SOURCE_FILES})

target_include_directories(benchmarking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(benchmarking PUBLIC
        benchmark::benchmark -lpthread
        dataManager
        ordering-system
        tradingStrategies
        )

add_executable(benchmarker ${SOURCE_FILES})
target_link_libraries(benchmarker benchmarking)

install(TARGETS benchmarker DESTINATION bin)


