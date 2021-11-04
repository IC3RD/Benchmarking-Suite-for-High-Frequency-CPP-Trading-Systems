cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES BollingerBand.cpp)

add_library(bollingerBand ${SOURCE_FILES})

target_include_directories(bollingerBand PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bollingerBand PUBLIC
        Foundation
        Crypto
        Util
        JSON
        NetSSL
        exchange
        ordering-system)