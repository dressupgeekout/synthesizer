#!/bin/sh

set -ex

export CC=x86_64-w64-mingw32-gcc
export LD=x86_64-w64-mingw32-gcc


mkdir -p ./build-windows

cd ./build-windows

cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_SYSTEM_NAME=Windows
make  VERBOSE=1 -j1

cd -
