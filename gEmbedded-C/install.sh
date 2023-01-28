#!/bin/bash

TARGET_API="../library/gEmbedded-C/api"
TARGET_LIBRARY="../library/gEmbedded-C/lib"

rm -rf ${TARGET_API}
mkdir ${TARGET_API}
rm -rf ${TARGET_LIBRARY}
mkdir ${TARGET_LIBRARY}

cp ./common/inc/common.h ${TARGET_API}
cp ./pin/inc/*.h ${TARGET_API}
cp ./i2c/inc/*.h ${TARGET_API}

cp ./build/libgEmbedded-C.a  ${TARGET_LIBRARY}
