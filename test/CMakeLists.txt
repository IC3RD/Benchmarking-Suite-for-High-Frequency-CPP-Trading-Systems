cmake_minimum_required(VERSION 3.2)
project(tests)

#enable_testing()

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

set(EXAMPLE_TESTS_SOURCE_FILES src/example_tests.cpp)
set(ORDERDATA_TESTS_SOURCE_FILES src/orderdata_tests.cpp ../src/dataManager/OrderData.cpp)
set(LISTENER_TESTS_SOURCE_FILES src/listener_tests.cpp ../../src/dataManager/OrderBook.cpp ../../src/dataManager/OrderData.cpp ../../src/dataManager/OrderDataStore.cpp ../../src/orderDataCollectors/OrderDataCollector.cpp ../../src/orderDataCollectors/fileReaderListener/FileReaderListener.cpp)
set(ORDERBOOK_TESTS_SOURCE_FILES src/orderbook_tests.cpp ../../src/dataManager/OrderBook.cpp ../../src/dataManager/OrderDataStore.cpp)
set(ORDERDATASTORE_TESTS_SOURCE_FILES src/orderdatastore_tests.cpp ../../src/dataManager/OrderDataStore.cpp)
set(BAND_TESTS_SOURCE_FILES src/band_tests.cpp ../src/tradingStrategies/bollingerBand/Band.cpp)

set(SOURCE_FILES main.cpp ${EXAMPLE_TESTS_SOURCE_FILES} ${ORDERDATA_TESTS_SOURCE_FILES} ${LISTENER_TESTS_SOURCE_FILES} ${ORDERBOOK_TESTS_SOURCE_FILES} ${ORDERDATASTORE_TESTS_SOURCE_FILES} ${BAND_TESTS_SOURCE_FILES})
add_executable(tests ${SOURCE_FILES})

target_link_libraries(tests gtest
        curl
        Foundation
        ixwebsocket
        Crypto
        Util
        JSON
        )
install(TARGETS tests DESTINATION bin)
