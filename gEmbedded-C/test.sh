#!/bin/bash

./compile.sh

ssh sondahi@192.168.1.4 "cd /home/sondahi; rm -f ./gEmbedded-C_test"
scp ./build/gEmbedded-C_test sondahi@192.168.1.4:/home/sondahi
ssh sondahi@192.168.1.4 "cd /home/sondahi; sudo ./gEmbedded-C_test"