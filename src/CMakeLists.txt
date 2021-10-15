cmake_minimum_required(VERSION 3.17)
project(CPPDesignPatternsforLowLatencyTrading)

set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
install(TARGETS main DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})

target_link_libraries(main ixwebsocket)
