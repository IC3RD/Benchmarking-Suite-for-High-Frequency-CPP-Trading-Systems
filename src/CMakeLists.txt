cmake_minimum_required(VERSION 3.17)
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

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
install(TARGETS main DESTINATION ${INSTALL_BIN_DIR})

target_link_libraries(main PUBLIC
        ixwebsocket
        listener
        dataManager
        tradingStrategies
        ordering-system
        #concurrentUnorderedSet
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
add_subdirectory(concurrentUnorderedSet)
add_subdirectory(ordering-system)


