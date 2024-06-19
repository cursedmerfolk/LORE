cmake_minimum_required(VERSION 3.10)
project(LORE)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Include SWIG module
set_source_files_properties(wrapper.i PROPERTIES CPLUSPLUS ON)
swig_add_library(game_java LANGUAGE java SOURCES wrapper.i ${SOURCES})
# swig_add_library(game_python LANGUAGE python SOURCES wrapper.i ${SOURCES})
swig_add_library(game_csharp LANGUAGE csharp SOURCES wrapper.i ${SOURCES})

# I had to use both pkg_check_modules and find_package(jsoncpp) for some reason.
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})

find_package(jsoncpp REQUIRED)
target_link_libraries(game_java jsoncpp_lib)
# target_link_libraries(game_python jsoncpp_lib)
target_link_libraries(game_csharp jsoncpp_lib)
