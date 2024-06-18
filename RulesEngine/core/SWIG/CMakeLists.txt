cmake_minimum_required(VERSION 3.10)
project(GameBindings)

# Find Python
find_package(Python COMPONENTS Development)

# Include directories for Python
include_directories(${Python_INCLUDE_DIRS})

# SWIG module
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

include_directories(/usr/lib/jvm/java-11-openjdk-amd64/include)
include_directories(/usr/lib/jvm/java-11-openjdk-amd64/include/linux)

# Set SWIG flags
set(CMAKE_SWIG_FLAGS "")

# Header and source files
file(GLOB HEADERS "../include/*.h")
file(GLOB SOURCES "../src/*.cpp")

# Include SWIG module
set_source_files_properties(wrapper.i PROPERTIES CPLUSPLUS ON)
swig_add_library(game_java LANGUAGE java SOURCES wrapper.i ${HEADERS} ${SOURCES})
# swig_add_library(game_python LANGUAGE python SOURCES wrapper.i ${HEADERS} ${SOURCES})
swig_add_library(game_csharp LANGUAGE csharp SOURCES wrapper.i ${HEADERS} ${SOURCES})

# Set output directory for Java JNI library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Install target (optional for Java)
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
install(TARGETS game_java DESTINATION ${CMAKE_INSTALL_PREFIX})
# install(TARGETS game_python DESTINATION ${CMAKE_INSTALL_PREFIX})
install(TARGETS game_csharp DESTINATION ${CMAKE_INSTALL_PREFIX})
