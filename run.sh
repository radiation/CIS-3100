#!/bin/sh

mkdir -p ../build

g++ -o ../build/${1} ${1}.cpp && ../build/${1}
