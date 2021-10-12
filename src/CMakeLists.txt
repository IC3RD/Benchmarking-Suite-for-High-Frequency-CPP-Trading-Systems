cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES main.cpp)

add_executable(CPPDesignPatternsforLowLatencyTrading ${SOURCE_FILES})
install(TARGETS CPPDesignPatternsforLowLatencyTrading DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})