cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

SET(ENABLE_CPP_BENCHMARKS FALSE CACHE BOOL "Option to enable benchmarking.")
if (ENABLE_CPP_BENCHMARKS)
    message(">>> !!Benchmarking ENABLED...")
    add_definitions(-DENABLE_CPP_BENCHMARKS)
else()
    message(">>> !!Benchmarking DISABLED...")
endif()

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


