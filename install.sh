#!/bin/bash

set -e
mkdir -p build
cd build
cmake ..
cmake --build .
echo "Build complete. You can now run run.sh"
