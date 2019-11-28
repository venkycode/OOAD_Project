#!/bin/bash
sudo apt-get install python3.6
sudo apt-get install python3.6-dev
export CPATH=/usr/include/python3.6m
echo "Done!"
g++ -o m main.cpp -lsqlite3 -lpython3.6m
./m
