project(benchmarking)

add_subdirectory(lib/benchmark)
include_directories(lib/benchmark/include ../tests/lib/googletest/googletest/include)

set(SOURCE_FILES benchmarking.cpp)
add_executable(benchmarking ${SOURCE_FILES})
target_link_libraries(benchmarking
        benchmark::benchmark -lpthread
)

install(TARGETS benchmarking DESTINATION bin)


