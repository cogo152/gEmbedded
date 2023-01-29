#!/bin/bash

TARGET_API="../library/gEmbedded-C/inc"
TARGET_LIBRARY="../library/gEmbedded-C/lib"

rm -rf ${TARGET_API}
mkdir ${TARGET_API}
rm -rf ${TARGET_LIBRARY}
mkdir ${TARGET_LIBRARY}

cp ./controller/inc/*.h ${TARGET_API}
cp ./build/libgEmbedded-C.a  ${TARGET_LIBRARY}
