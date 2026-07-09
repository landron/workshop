#!/usr/bin/env bash
set -e

cmake -G Ninja ./
ninja
ctest -V
./cpp_tests
