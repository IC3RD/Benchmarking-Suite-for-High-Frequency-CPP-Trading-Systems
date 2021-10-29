# CPP-design-pattern-for-low-latency

IC 3rd year computing group project

Good introduction to CMake: https://cliutils.gitlab.io/modern-cmake/

## Requirements
**OS X**:

1. Install cmake: `brew install cmake`
1. Install gcc10+: `brew install gcc@10`
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
   

## Naming convention

branch name: \<issue-key\>-\<branch-name\>

e.g. `git checkout -b JRA-123-firstbranch`

commit message: "\<issue-key\> \<commit message\>"

e.g. `git  commit -m "JRA-123 first message"`
