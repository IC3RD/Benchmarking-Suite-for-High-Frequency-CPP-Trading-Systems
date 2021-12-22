rm -rf build && mkdir build
git pull --recurse-submodules
cmake -S . -B build
cmake --build build
cmake --install build
