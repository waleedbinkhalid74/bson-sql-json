#!/bin/bash

cd ..
cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build . -- -j1
ctest --output-on-failure
