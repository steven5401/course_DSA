#!/bin/bash 
if [ $@ ];then
    echo "compile with -g"
    g++ project.cpp -g -std=c++11 -o project.out
else
    g++ project.cpp -O3 -std=c++11 -o project.out
fi
