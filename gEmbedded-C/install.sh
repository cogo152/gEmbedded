#!/bin/bash

TARGET_DIRECTORY="../library/gEmbedded-C"

rm -rf ${TARGET_DIRECTORY}
mkdir ${TARGET_DIRECTORY}
mkdir ${TARGET_DIRECTORY}/inc

cp ./common/inc/*.h ${TARGET_DIRECTORY}/inc
cp ./pin/inc/*.h ${TARGET_DIRECTORY}/inc
cp ./build/libgEmbedded-C.a ${TARGET_DIRECTORY}
