cmake_minimum_required(VERSION 3.2)
project(tests)

add_definitions(-fprofile-arcs -ftest-coverage)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -O0 -Wall -fprofile-arcs -ftest-coverage")

enable_testing()

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

set(EXCHANGE_EXECS_DIR ../src/ordering-system/exchangeExecutors)
set(EXCHANGE_EXECS_SRC_FILES ${EXCHANGE_EXECS_DIR}/ExchangeOrderExecutor.cpp ${EXCHANGE_EXECS_DIR}/binance/BinanceOrderExecutor.cpp ${EXCHANGE_EXECS_DIR}/bitmex/BitmexOrderExecutor.cpp ${EXCHANGE_EXECS_DIR}/coinbase/CoinbaseOrderExecutor.cpp)

set(EXAMPLE_TESTS_SOURCE_FILES src/example_tests.cpp)
set(ORDERDATA_TESTS_SOURCE_FILES src/orderdata_tests.cpp ../src/dataManager/OrderData.cpp)
set(LISTENER_TESTS_SOURCE_FILES src/listener_tests.cpp ../../src/dataManager/OrderBook.cpp ../../src/dataManager/OrderData.cpp ../../src/dataManager/OrderDataStore.cpp ../../src/orderDataCollectors/OrderDataCollector.cpp ../../src/orderDataCollectors/fileReaderListener/FileReaderListener.cpp)
set(ORDERS_TESTS_SOURCE_FILES src/order_tests.cpp ../../src/dataManager/Order.cpp)
set(ORDERBOOK_TESTS_SOURCE_FILES src/orderbook_tests.cpp ../../src/dataManager/OrderBook.cpp ../../src/dataManager/OrderDataStore.cpp)
set(ORDERDATASTORE_TESTS_SOURCE_FILES src/orderdatastore_tests.cpp ../../src/dataManager/OrderDataStore.cpp)
set(BAND_TESTS_SOURCE_FILES src/band_tests.cpp ../src/tradingStrategies/bollingerBand/Band.cpp)
set(ORDER_MANAGER_TESTS_SOURCE_FILES src/order_manager_tests.cpp ../src/ordering-system/OrderManager.cpp ../src/dataManager/Order.cpp ${EXCHANGE_EXECS_SRC_FILES})
set(ORDER_EXECUTOR_TESTS_SOURCE_FILES src/order_executor_tests.cpp) 
set(TRADING_STRATEGY_TESTS_SOURCE_FILES src/trading_strategy_tests.cpp ../src/tradingStrategies/TradingStrategy.cpp ../src/tradingStrategies/bollingerBand/BollingerBand.cpp)
set(BOLLINGER_STRATEGY_TESTS_SOURCE_FILES src/bollinger_strategy_tests.cpp)
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/test/CMakeFiles/tests.dir/src)

set(SOURCE_FILES main.cpp ${TRADING_STRATEGY_TESTS_SOURCE_FILES} ${EXAMPLE_TESTS_SOURCE_FILES} ${ORDERDATA_TESTS_SOURCE_FILES} ${LISTENER_TESTS_SOURCE_FILES} ${ORDERBOOK_TESTS_SOURCE_FILES} ${ORDERDATASTORE_TESTS_SOURCE_FILES} ${BAND_TESTS_SOURCE_FILES} ${ORDERS_TESTS_SOURCE_FILES} ${ORDER_MANAGER_TESTS_SOURCE_FILES} ${ORDER_EXECUTOR_TESTS_SOURCE_FILES} ${BOLLINGER_STRATEGY_TESTS_SOURCE_FILES})
add_executable(tests ${SOURCE_FILES})

add_custom_target(gcov
        COMMAND mkdir -p gcoverage
        COMMAND ${CMAKE_MAKE_PROGRAM} test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
add_custom_command(TARGET gcov
        COMMAND echo "=================== GCOV ===================="
        COMMAND gcov -o ${OBJECT_DIR} ${CMAKE_SOURCE_DIR}/test/src/*.cpp
        COMMAND echo "-- Source diretorie: ${CMAKE_SOURCE_DIR}/test/src/"
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
        )

add_custom_target(lcov
        COMMAND mkdir -p lcoverage
        )
add_custom_command(TARGET lcov
        COMMAND echo "=================== LCOV ===================="
        COMMAND echo "-- Passing lcov tool under code coverage"
        COMMAND lcov --capture --directory ../ --output-file lcoverage/main_coverage.info
        COMMAND lcov --remove lcoverage/main_coverage.info "/usr/include/*" "/usr/local/*" "*asio/*" "*googletest/*" "*test/*" "*lib/*" "*include/*" --output-file lcoverage/main_coverage.info
        COMMAND echo "-- Generating HTML output files"
        COMMAND genhtml lcoverage/main_coverage.info --output-directory lcoverage
        )

target_link_libraries(tests gtest
        curl
        Foundation
        ixwebsocket
        Crypto
        Util
        JSON
        ordering-system
        )

install(TARGETS tests DESTINATION bin)
