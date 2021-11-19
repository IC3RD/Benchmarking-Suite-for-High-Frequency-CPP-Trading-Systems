cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES OrderBook.cpp OrderDataStore.cpp Order.cpp
        OrderData.cpp
        OrderTypes.h)

add_library(dataManager ${SOURCE_FILES})

target_link_libraries(dataManager PUBLIC
        JSON exchange concurrentUnorderedSet ordering-system)
