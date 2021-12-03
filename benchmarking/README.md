# Benchmarking Suite Usage
[Back to home page](../README.md)

This `README.md` outlines how to use the benchmarking suite.

There are two main components:

1. [Extensible benchmarking functionality for individual functions and the entire hotpath.](#extensible-benchmarking)

2. [Automatic report generation](#automatic-report-generation)


## Extensible Benchmarking
The file `src/benchmarking.cpp` is typically where you would define benchmarking tests. Benchmarking is implemented using *Google Benchmark*.



### Running the Benchmarks
Run the following commands from the project root directory (i.e `CPP-design-pattern-for-low-latency/`).
```shell
cmake -S . -DBENCHMARK_HOTPATH:BOOL=True/False -DENABLE_CPP_BENCHMARKS:BOOL=True/False -B build
cmake --build build
cmake --install build
```
Make sure to appropiately set the benchmarking flags (`-DBENCHMARK_HOTPATH` and `-DENABLE_CPP_BENCHMARKS`) .

<u>Note</u> - these two options are mutually exclusive. You **cannot** enable hotpath benchmarking and per function benchmarking at the same time.

If attempted Cmake will throw an error *"Invalid flag combination. Cannot benchmark hotpath and individual functions at the same time.".*

If you'd like to switch from one mode to another, you must follow the above steps again with the appropriate flag selection.



### Benchmarking Individual Functions

Ensure  `-DBENCHMARK_HOTPATH:BOOL=False` and `-DENABLE_CPP_BENCHMARKS:BOOL=True`.

Define benchmarks in `src/benchmarking.cpp`. There are sample implementations defined in the file for reference.

***

Wrap your benchmarking code with the following preprocessor directive:

```cpp
#if defined(ENABLE_CPP_BENCHMARKS) && !defined(BENCHMARK_HOTPATH)
static void exampleBenchmark(benchmark::State &state) {
  // Run benchmark here...
};
BENCHMARK(exampleBenchmark);
#endif
```

This will ensure the benchmark only runs when you intend to benchmark individual functions.

***

The preprocessor definition `ENABLE_CPP_BENCHMARKS` is particularly useful in preventing code from running.

Consider the following use case. Say we wanted to benchmark a function:

```cpp
void functionToBenchmark() {
  // Some work is done here...
  callToAnotherFunction();
}
```

In our benchmarking suite, we'd like to generate and record results to `functionToBenchmark()` individually, disregarding the call to `callToAnotherFunction()` in our final time.

Simply wrap the function call using the `ENABLE_CPP_BENCHMARKS` definition:

```cpp
void functionToBenchmark() {
  // Some work is done here...
#ifndef ENABLE_CPP_BENCHMARKS
  callToAnotherFunction();
#endif
}
```

***

For an example implementation, consider `CPP-design-pattern-for-low-latency/src/ordering-system/exchangeExecutors/utils/CurlManager.cpp` that disables curl execution whilst benchmarking.

```CPP
// CurlManager.cpp
void CurlManager::addPostFields(const std::string& fields) {
#if !(defined(ENABLE_CPP_BENCHMARKS) || defined(BENCHMARK_HOTPATH))
  curl_easy_setopt(this->curl, CURLOPT_POST, 1L);
  curl_easy_setopt(this->curl, CURLOPT_POSTFIELDS, fields.c_str());
  curl_easy_setopt(this->curl, CURLOPT_POSTFIELDSIZE, fields.length());
#endif
}
```



### Benchmarking the Hotpath

Ensure `-DBENCHMARK_HOTPATH:BOOL=True` and `-DENABLE_CPP_BENCHMARKS:BOOL=False`.

Define benchmarks in `src/benchmarking.cpp`. There is a sample implementation defined in the file for reference.

***

Wrap your benchmarking code with the following preprocessor directive:

```cpp
#if !defined(ENABLE_CPP_BENCHMARKS) && defined(BENCHMARK_HOTPATH)
static void exampleBenchmark(benchmark::State &state) {
  // Run benchmark here...
};
BENCHMARK(exampleBenchmark);
#endif
```

This will ensure the benchmark only runs when you intend to benchmark the entire hotpath.

***

The preprocessor definition `BENCHMARK_HOTPATH` is particularly useful in disabling certain pieces of code.

Consider the following use case. Suppose there is a particular function call in your code that is unlikely to be used in an actual implementation. That is to say, there is some timely function call that would realistically be implemented in a full trading system, but for the purposes of benchmarking needs to be removed as it skews results.

In our case, consider Poco's implementation of HMAC SHA-256 which is used in an `ExchangeOrderExecutor` authentication procedure.

```cpp
// BitmexOrderExecutor.cpp
std::string BitmexOrderExecutor::generateSignature(
    const std::string &message, const std::string &timestamp) {
  SHA256Engine engine{};
  std::string verb = "POST";
  std::string path = "/api/v1/order";
  Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};
  hmac.update(verb + path + timestamp + message);
  std::string hmac_hex = Poco::DigestEngine::digestToHex(hmac.digest());
  return hmac_hex;
}
```

The call to `hmac.update(verb + path + timestamp + message);` takes upwards of 30,000ns. Consider the fact that a typical hotpath run of this implementation takes <1,000ns without the call. The hotpath result will be of > 30,000ns - a pretty unhelpful result.

To mitigate this, we should disable the call, and perhaps replace it with a suitable procedure that emulates a realistic runtime.

```cpp
// BitmexOrderExecutor.cpp
std::string BitmexOrderExecutor::generateSignature(
    const std::string &message, const std::string &timestamp) {
  SHA256Engine engine{};
  std::string verb = "POST";
  std::string path = "/api/v1/order";
#ifdef BENCHMARK_HOTPATH
  return "a fake signature";
#else
  Poco::HMACEngine<SHA256Engine> hmac{getSecretKey()};
  hmac.update(verb + path + timestamp + message);
  std::string hmac_hex = Poco::DigestEngine::digestToHex(hmac.digest());
  return hmac_hex;
#endif
}
```



### Frequently Asked Questions

**Why is there a separate flag for the hotpath?**

Enabling `-DENABLE_CPP_BENCHMARKS:BOOL` would prevent calls to other functions for whenever the `ENABLE_CPP_BENCHMARKS` is used to omit code in the implementation. As a result the hotpath would be incomplete/broken.

**Why can't I just benchmark the system without any flags enabled?**

The hotpath is defined as the flow of execution starting when the program receives data, up to the point where it sends data.

The system, by default, is a full implementation of an entire automated trading system. This includes fetching data from the exchange via WebSocket, to processing and executing an order over HTTP using libcurl.

A benchmark over the entire system (i.e. compiling without any flags), would include these extra steps in the time it returns.

As a result, to remain consistent with the fact we are benchmarking solely the hotpath, we use such flags to disable those functionalities.

**It takes too long to switch between benchmarking modes!**

Unfortunately that's the consequence of using preprocessor directives - files need to be recompiled.

**How can I tell which mode is enabled?**

Upon running `cmake -S . -DBENCHMARK_HOTPATH:BOOL=True/False -DENABLE_CPP_BENCHMARKS:BOOL=True/False -B build`, you should get a message akin to `>>> !!Hotpath Benchmarking/Benchmarking ENABLED/DISABLED...`



## Automatic Report Generation
### Set-Up and Prerequisites
*Note: This script is meant for Linux machines - it will not work for any other OS*
1. Set the venv folder in the root directory of the project as your python interpreter
2. Build the project as specified in the root directory [README.md](../README.md) file
3. Load (run) the `CMakeLists.txt` file in the root directory to get the benchmarker executable
4. Move to `CPP-design-pattern-for-low-latency/benchmarking` directory before running the script
5. Output files from the script will be written to `/outputs/benchmarking` folder

### Running the script
1. Run `./benchmarking_script.py [args] [options]` with args and options as below

- *Note: The script is configured to be run with three different configurations (based on the number of arguments provided):*
##### Number of arguments:
####### No arguments:
- This will run the benchmarking with results printed in the **terminal**

####### One argument:

- Giving the script a **file name** as an argument will cause it to run the benchmarker and then compare the results with the
  results in the given file.
- The script produces a report which will be saved in the `/outputs` folder as a pdf.
- **Make sure the file given as an argument is in the `/outputs` folder**

####### Two arguments:
- Giving the script **two file names** as arguments will cause it to compare the results of the given files.
- The script produces a report which will be saved in the `/outputs` folder as a pdf.
- **Make sure the given files are in the `/outputs` folder**

##### Notes:
* Please make sure you run it at least once without arguments (to produce at least one file)
* The script is configured to work with files it has previously produced (to get the correct format), so do not try to
  run it with your own files.
* The naming conventions used are:
    * `benchmark_at[DATE_TIME]` for files produced by the benchmarker (json files)
    * `comparison_[FILE_1]_[FILE_2].pdf` for each report produced
        * here `FILE_1` and `FILE_2` are named as `benchamark_at[DATE_TIME]` as mentioned above

##### Options:
* `-h` or `--help`: get help
* `-output-path OUTPUT_PATH` or `--out OUTPUT_PATH`: specify the path for the outputted files (default `/outputs`)
* `-input-path INPUT_PATH` or `--in INPUT_PATH`: specify the path for the input files (default `/outputs`)



[Back to home page](../README.md)


