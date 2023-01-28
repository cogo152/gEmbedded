#!/bin/bash

/usr/bin/cmake  -DCMAKE_BUILD_TYPE=Release \
                -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja \
                -G "Ninja" \
                -S . \
                -B ./build