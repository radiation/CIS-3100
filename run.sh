#!/bin/sh

mkdir -p ../build

g++ -std=c++20 -o ../build/${1} ${1}.cpp && ../build/${1}
