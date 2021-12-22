mkdir build || true
git pull --recurse-submodules
cmake -S . -B build
cmake --build build
cmake --install build
