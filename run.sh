#!/bin/bash

# Ensure script exits on error
set -e

# Require build flag
if [[ "$1" != "Release" && "$1" != "Debug" ]]; then
    echo "Usage: ./build.sh Release or Debug"
    exit 1
fi

BUILD_TYPE=$1
BUILD_DIR="out/$BUILD_TYPE"
EXECUTABLE="$BUILD_DIR/MazeGen"

# Check if the executable exists
if [[ -f "$EXECUTABLE" ]]; then
    # Change to the build directory so maze files save correctly
    cd "$BUILD_DIR"
    echo "Starting MazeGen..."
    ./"MazeGen" &
else
    echo "Could not find executable file. Please run ./compile.sh in the main directory first!"
fi
