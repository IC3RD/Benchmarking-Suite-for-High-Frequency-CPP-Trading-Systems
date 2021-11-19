cmake_minimum_required(VERSION 3.2)
project(tests)

#enable_testing()

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

set(EXAMPLE_TESTS_SOURCE_FILES src/example_tests.cpp)
set(BOLLINGER_BAND_TESTS_SOURCE_FILES src/bollingerBand_tests.cpp ../src/tradingStrategies/bollingerBand/BollingerBand.cpp ../src/dataManager/Order.cpp
        ../src/exchange/Exchange.h)
set(MARKET_DATA_TESTS ../src/exchange/Exchange.h)
set(SOURCE_FILES main.cpp ${EXAMPLE_TESTS_SOURCE_FILES} ${BOLLINGER_BAND_TESTS_SOURCE_FILES} ${MARKET_DATA_TESTS})
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests gtest
        bollingerBand
        exchange
        curl
        Foundation
        Crypto
        Util
        JSON 
)
install(TARGETS tests DESTINATION bin)
