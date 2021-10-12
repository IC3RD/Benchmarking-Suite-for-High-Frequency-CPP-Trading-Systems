rm -rf build && mkdir build
git submodule init && git submodule update
cd build || exit
cmake ..
make & make install
cd ..