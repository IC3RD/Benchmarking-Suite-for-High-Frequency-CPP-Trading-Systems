# CPP-design-pattern-for-low-latency

IC 3rd year computing group project

Good introduction to CMake: https://cliutils.gitlab.io/modern-cmake/

## Requirements
**OS X**:

1. Install cmake: `brew install cmake`
1. Install gcc11.2+: `brew install gcc@11`
1. Check gcc is correctly installed: `g++-11 --version`
1. Install clang-format: `brew install clang-format`

## Setup
1. Check out submodules: `git submodule update --init --recursive`
1. Configure CMake: `cmake -S . -B build`

## Build
1. Run `cmake --build build`
1. Install the files with: `cmake --install build`

## Testing
1. Build
2. Run `bin/tests`

## Running
1. Build
2. Run `bin/main`

## Naming convention

branch name: \<issue-key\>-\<branch-name\>

e.g. `git checkout -b JRA-123-firstbranch`

commit message: "\<issue-key\> \<commit message\>"

e.g. `git  commit -m "JRA-123 first message"`
