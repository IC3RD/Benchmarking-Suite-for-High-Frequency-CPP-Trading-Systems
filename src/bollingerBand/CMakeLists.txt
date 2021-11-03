cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES BollingerBand.cpp Logger.cpp MarketData.cpp AlgoTrader.cpp Order.cpp BitMEXApi.cpp SHA256Engine.cpp SHA256Engine.h)

add_library(bollingerBand ${SOURCE_FILES})

target_include_directories(bollingerBand PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(bollingerBand PUBLIC
        Foundation
        Crypto
        Util
        JSON
        NetSSL ordering-system)