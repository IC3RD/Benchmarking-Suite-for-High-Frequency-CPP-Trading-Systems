cmake_minimum_required(VERSION 3.2)
project(tests)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/main_tests.cpp)

add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests gtest)
install(TARGETS tests DESTINATION bin)