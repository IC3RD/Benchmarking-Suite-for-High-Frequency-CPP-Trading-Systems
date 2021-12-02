project(CPPDesignPatternsforLowLatencyTrading)

SET(ENABLE_CPP_BENCHMARKS FALSE CACHE BOOL "Option to enable benchmarking.")
SET(BENCHMARK_HOTPATH FALSE CACHE BOOL "Option to enable hotpath benchmarking
.")

if (ENABLE_CPP_BENCHMARKS AND BENCHMARK_HOTPATH)
    message( SEND_ERROR "Invalid flag combination. Cannot benchmark hotpath and
   individual functions at the same time." )
endif()

if (ENABLE_CPP_BENCHMARKS)
    message(">>> !!Benchmarking ENABLED...")
    add_definitions(-DENABLE_CPP_BENCHMARKS)
else ()
    message(">>> !!Benchmarking DISABLED...")
endif ()

if (BENCHMARK_HOTPATH)
    message(">>> !!Hotpath Benchmarking ENABLED...")
    add_definitions(-DBENCHMARK_HOTPATH)
else ()
    message(">>> !!Hotpath Benchmarking DISABLED...")
endif ()

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
        orderDataCollectors
        )

add_executable(benchmarker ${SOURCE_FILES})
target_link_libraries(benchmarker benchmarking)

install(TARGETS benchmarker DESTINATION bin)


