#!/bin/sh
mkdir -p build && \
cd build/ &&
cmake .. && \
make

if [ "$(basename ${PWD})" == "build" ]; then
    cd ..
fi
