cmake_minimum_required(VERSION 3.2)
project(tests)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/main_tests.cpp)
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests gtest)
install(TARGETS tests DESTINATION bin)

#set(BOLLINGER_SOURCE_FILES src/bollingerBand_tests.cpp ../src/bollingerBand/BollingerBand.cpp ../src/bollingerBand/MarketData.cpp ../src/bollingerBand/Logger.cpp)
#add_executable(bollinger_tests ${BOLLINGER_SOURCE_FILES})
#target_link_libraries(bollinger_tests gtest)
#install(TARGETS bollinger_tests DESTINATION bin)
