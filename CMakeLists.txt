cmake_minimum_required(VERSION 3.10)

# Project name
project(MazeGen CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

# Explicitly set output for different build types (MSVC fix)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BUILD_DIR}/RelWithDebInfo)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${BUILD_DIR}/MinSizeRel)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find all source files
file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Debug mode definitions
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG=1)
endif()
