cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES OrderManager.cpp OrderManager.h OrderBuilder.cpp OrderBuilder.h)

add_library(ordering-system ${SOURCE_FILES})

target_include_directories(ordering-system PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ordering-system PUBLIC bollingerBand)

add_subdirectory(coinbase)