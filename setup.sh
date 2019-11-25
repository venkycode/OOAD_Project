#!/bin/bash
sudo apt-get install python3.6
sudo apt-get install python3.6-dev
export CPATH=$PATH:/usr/include/python3.6m
g++ main.cpp -lsqlite3 -lpyhton3.6 -o main
echo "Starting Program !!"
sleep 2s
./main
