cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

SET(ENABLE_CPP_BENCHMARKS FALSE CACHE BOOL "Option to enable benchmarking.")
SET(BENCHMARK_HOTPATH FALSE CACHE BOOL "Option to enable hotpath benchmarking
.")

if (ENABLE_CPP_BENCHMARKS)
    add_definitions(-DENABLE_CPP_BENCHMARKS)
endif ()

if (BENCHMARK_HOTPATH)
    add_definitions(-DBENCHMARK_HOTPATH)
endif ()

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
install(TARGETS main DESTINATION ${INSTALL_BIN_DIR})

target_link_libraries(main PUBLIC
        ixwebsocket
        listener
        dataManager
        tradingStrategies
        ordering-system
        curl
        Foundation
        Crypto
        Util
        JSON
        NetSSL
        OpenSSL::SSL
        )

add_subdirectory(tradingStrategies)
add_subdirectory(orderDataCollectors)
add_subdirectory(dataManager)
add_subdirectory(ordering-system)


