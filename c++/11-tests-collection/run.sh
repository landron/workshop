#!/usr/bin/env bash
#
#   cmake build folder: ../../mine/workshop/c++/11-tests-collection/run.sh
#
set -e

cmake -G Ninja ./
ninja
ctest -V
./cpp_tests
