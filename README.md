# CPP-design-pattern-for-low-latency

IC 3rd year computing group project

Good introduction to CMake: https://cliutils.gitlab.io/modern-cmake/

## Requirements
**OS X**:

1. Install cmake: `brew install cmake`
1. Install gcc10+: `brew install gcc@10`
1. Install libcurl.
1. Check gcc is correctly installed: `g++-10 --version`
1. Install clang-format: `brew install clang-format`

## Setup
1. Check out submodules: `git submodule update --init --recursive`

## Build
1. Generate build Makefiles: `cmake -S . -B build`
1. Run `cmake --build build`
1. Install the files with: `cmake --install build`

## Testing
1. Build
2. Run `bin/tests`

## Running
1. Build
2. Run `bin/main`

## Set up CLion
For some strange mysterious reason, CLion uses their own version of CMake 
rather than the one installed in the system. Their version doesn't fully 
support C++17 and causes issues in compiling some of our code. 

To change it, it's worth to edit some settings:

1. In `Build, Execution, Deployment`, please make sure to edit CMake, GCC \& 
   G++ to point to your own versions (location of which you can get with 
   running `which <command>`).
1. In CMake settings, please select `Build Directory` as `build/`.

# Benchmarking

## Running Google Benchmark
TODO

## Running perf

We use `perf` as our tool to profile our code. The advantages of perf are that it adds no extra overhead onto running processes - it simply samples stack frame at certain intervals. This ensure that the results as close to "real performance" as possible.

As a summary of your performance, we generate an HTML interactive FlameGraph that allows you to explore your call stacks.

To investigate more, we recommend you to run `perf report` and investigate call stacks and annotations (code).

To run perf, please follow the following steps:

1. Follow the steps for Build
1. Run `sudo ./benchmark-perf.sh {html_output_filename}`
1. Press CTRL-C after 1-2 minutes of the profiler running.
1. Explore output in your favourite favourite browser.

Please bear in mind that perf work on *Linux-only.*

## Naming convention

branch name: \<issue-key\>-\<branch-name\>

e.g. `git checkout -b JRA-123-firstbranch`

commit message: "\<issue-key\> \<commit message\>"

e.g. `git  commit -m "JRA-123 first message"`

## Implementing your own code for benchmarking

#### Adding a new exchange/changing data input feed  

###### Getting data from exchanges 
1. Create a new listener for the exchange to implement `Listener.h` methods, namely `passJSON(nlohmann::json json)`
2. OPTIONAL: To change how order data is constructed and sent edit the methods in `Listener.cpp` as desired

###### Getting data from a custom plae
1. Implement methods from `OrderDataCollector.h` in a custom listener. Look at the `fileReaderListener` for an example
of how to do this.
2. Update CMake files as required

#### Executing orders

###### Sending orders to an exchange 

1. Create a new order executor to implement `ExchangeOrderExecutor.h` methods in the ordering-system/exchangeExecutors folder
2. Update `Exchange.h` to contain the exchange name as an enum
3. Add new files to source files within `ordering-system/CMakeLists.txt`

###### Sending orders to a custom file/place

1. Create a new type of executor class to implement `OrderExecutor.h` similarly to `ExchangeOrderExecutor.h`
2. Update CMake files as appropriate

#### Adding a new trading strategy/algo

1. Create a new algo to implement methods in `TradingStrategy.h`
2. Add new files to source files within `tradingStrategies/CMakeLists.txt`
3. OPTIONAL: To change how and when to run the strategy itself, alter `updateData` method within `TradingStrategy.cpp`

#### Changing the map type within the order data system 

