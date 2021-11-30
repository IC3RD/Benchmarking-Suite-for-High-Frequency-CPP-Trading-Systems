project(CPPDesignPatternsforLowLatencyTrading)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(lib/benchmark)
include_directories(lib/benchmark/include)
#include_directories(../src/)
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
target_link_libraries(benchmarker benchmark::benchmark -lpthread
        dataManager
        ordering-system
        tradingStrategies)

install(TARGETS benchmarker DESTINATION bin)

SET(ENABLE_BENCHMARKS_XYZABC FALSE CACHE BOOL "Option to enable benchmarking.")
if (ENABLE_BENCHMARKS_XYZABC)
    message(">>> !!Benchmarking ENABLED...")
    set_property( TARGET benchmarking PROPERTY COMPILE_DEFINITIONS BENCHMARK_CPP_TEST=1 )
#    add_definitions(BENCHMARK_CPP_TEST)
else()
    message(">>> !!Benchmarking DISABLED...")
endif()


