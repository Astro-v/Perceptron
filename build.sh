#!/bin/bash

TOPDIR=$(pwd)

rm -rf build/
rm -rf bin/

mkdir build

cmake . -Bbuild

cd build

make