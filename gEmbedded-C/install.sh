#!/bin/bash

TARGET_DIRECTORY="../library/gEmbedded-C"

rm -rf ${TARGET_DIRECTORY}
mkdir ${TARGET_DIRECTORY}
mkdir ${TARGET_DIRECTORY}/inc

cp ./common/*.h ${TARGET_DIRECTORY}/inc
cp ./commontest/*.h ${TARGET_DIRECTORY}/inc
cp ./controller/inc/*.h ${TARGET_DIRECTORY}/inc
cp ./build/libgEmbedded-C.a ${TARGET_DIRECTORY}
