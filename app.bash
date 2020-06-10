#!/bin/bash
sudo apt-get install libsqlite3-dev
sudo apt-get install python3.7
sudo apt-get install python3.7-dev
export CPATH=/usr/include/python3.7m
echo "Done!"
g++ -o m main.cpp -lsqlite3 -lpython3.7m
./m
