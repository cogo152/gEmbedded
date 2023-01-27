#!/bin/bash

rm -rf ./build

/usr/bin/cmake -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_MAKE_PROGRAM=/usr/bin/ninja \
  -G "Ninja" \
  -S . \
  -B ./build

/usr/bin/cmake --build ./build --target gEmbedded-C
/usr/bin/cmake --build ./build --target gEmbedded-C_test

ssh sondahi@192.168.1.4 "cd /home/sondahi; rm -f ./gEmbedded-C_test"
scp ./build/gEmbedded-C_test sondahi@192.168.1.4:/home/sondahi
ssh sondahi@192.168.1.4 "cd /home/sondahi; sudo ./gEmbedded-C_test"

TARGET_API="../library/gEmbedded-C/api"
TARGET_LIBRARY="../library/gEmbedded-C/lib"

rm -rf ${TARGET_API}
mkdir ${TARGET_API}
rm -rf ${TARGET_LIBRARY}
mkdir ${TARGET_LIBRARY}

cp ./driver/common/inc/common.h ${TARGET_API}
cp ./driver/pin/inc/*.h ${TARGET_API}
cp ./driver/i2c/inc/*.h ${TARGET_API}

cp ./build/libgEmbedded-C.a  ${TARGET_LIBRARY}