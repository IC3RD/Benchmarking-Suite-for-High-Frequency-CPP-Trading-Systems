rm -rf build && mkdir build
git submodule update --init --recursive
cmake -S . -B build
cmake --build build
cmake --install build
