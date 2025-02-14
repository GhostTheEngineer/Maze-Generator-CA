#!/bin/bash

# Ensure script exits on error
set -e

# Require build flag
if [[ "$1" != "Release" && "$1" != "Debug" ]]; then
    echo "Usage: ./compile.sh Release or Debug"
    exit 1
fi

BUILD_TYPE=$1
BUILD_DIR="bin/$BUILD_TYPE"

# Create build directory if it does not exist
if [[ ! -d "$BUILD_DIR" ]]; then
    echo "Creating build directory..."
    mkdir -p "$BUILD_DIR"
fi

# Change directory to build folder
cd "$BUILD_DIR"

# Build the project
echo "Building in $BUILD_TYPE mode..."
cmake -S ../.. -B . -DCMAKE_BUILD_TYPE=$BUILD_TYPE
cmake --build .
