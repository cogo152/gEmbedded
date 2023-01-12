#!/bin/bash

./build.sh

/usr/bin/cmake  --build ./build --target gEmbedded-C      --verbose
/usr/bin/cmake  --build ./build --target gEmbedded-C_test --verbose