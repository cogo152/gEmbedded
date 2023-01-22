#!/bin/bash

rm -rf ../library/gEmbedded-C
mkdir ../library/gEmbedded-C
cp -r ./driver/api ../library/gEmbedded-C
cp ./build/libgEmbedded-C.a ../library/gEmbedded-C
