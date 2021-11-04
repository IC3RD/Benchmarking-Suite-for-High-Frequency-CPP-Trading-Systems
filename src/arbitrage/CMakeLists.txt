cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES Arbitrage.cpp )

add_library(arbitrage ${SOURCE_FILES})

target_include_directories(arbitrage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(arbitrage PUBLIC
        Foundation
        Crypto
        Util
        JSON
        NetSSL
        exchange)