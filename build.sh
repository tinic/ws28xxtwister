#!/bin/sh
set -e

git submodule update --init
cd pico-sdk
git submodule update --init
cd ..

mkdir -p build
cd build

build_type="Ninja"

rm -rf ws28xxtwister_*
mkdir -p ws28xxtwister_rel
cd ws28xxtwister_rel
cmake -G "$build_type" -DCMAKE_BUILD_TYPE=Release ../..
cmake --build .
cd ..
mkdir -p ws28xxtwister_dbg
cd ws28xxtwister_dbg
cmake -G "$build_type" -DCMAKE_BUILD_TYPE=Debug ../..
cmake --build .
cd ..
