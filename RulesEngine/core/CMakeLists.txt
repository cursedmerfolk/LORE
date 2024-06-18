cmake_minimum_required(VERSION 3.10)

# Project name
project(LORE)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Create the shared library
add_library(Name SHARED ${SOURCES})

# Specify the output name for the shared library
set_target_properties(Name PROPERTIES OUTPUT_NAME "Lore")
