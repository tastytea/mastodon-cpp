#!/bin/sh

if [ -f Doxyfile ]; then
    mkdir -p doc
    (cat Doxyfile && echo -n "PROJECT_NUMBER = " &&
       grep -Eo '[0-9]+.[0-9]+.[0-9]+$' CMakeLists.txt) \
       | doxygen -
fi
