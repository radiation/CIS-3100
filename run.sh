#!/bin/sh

g++ -std=c++20 -o /tmp/build/${1} ${1}.cpp && /tmp/build/${1}
