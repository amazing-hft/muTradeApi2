#bin/bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE="Debug" ..
wait
make
wait
