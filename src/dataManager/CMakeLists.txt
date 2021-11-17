cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES DataManager.cpp OrderBook.cpp OrderDataStore.cpp)

add_library(dataManager ${SOURCE_FILES})

target_link_libraries(dataManager PUBLIC
        JSON exchange concurrentUnorderedSet)
