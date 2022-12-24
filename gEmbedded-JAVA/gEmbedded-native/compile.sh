#!/bin/bash
rm -rf ./src/main/c/native/build

/usr/bin/cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/arm-linux-gnueabihf-gcc -S./src/main/c/native -B./src/main/c/native/build -G Ninja

/usr/bin/cmake --build ./src/main/c/native/build --config Release --target clean --

/usr/bin/cmake --build ./src/main/c/native/build --config Release --target all --