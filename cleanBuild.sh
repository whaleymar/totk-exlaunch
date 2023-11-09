#!/usr/bin/env bash
rm -r build/ && mkdir build && cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain.cmake && cmake --build .
