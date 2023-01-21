#!/bin/bash

./build.sh

/usr/bin/cmake  --build ./build --target gEmbedded-C
/usr/bin/cmake  --build ./build --target gEmbedded-C_test