cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES CoinbaseOrderManager.cpp CoinbaseOrderManager.h)

add_library(coinbase-manager ${SOURCE_FILES})

target_include_directories(coinbase-manager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(coinbase-manager PUBLIC ordering-system bollingerBand)
