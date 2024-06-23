cmake_minimum_required(VERSION 3.10)
project(LORE)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(DO_TESTS "Run the unit tests." OFF)

# Find Python
find_package(Python COMPONENTS Development)

# Include directories for Python
include_directories(${Python_INCLUDE_DIRS})

include_directories(${CMAKE_JS_INC})
link_directories(${CMAKE_JS_LIB})

# SWIG module
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

include_directories(/usr/lib/jvm/java-11-openjdk-amd64/include)
include_directories(/usr/lib/jvm/java-11-openjdk-amd64/include/linux)

# Set SWIG flags
set(CMAKE_SWIG_FLAGS "")

# Header and source files
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.cpp")

# I had to use both pkg_check_modules and find_package(jsoncpp) for some reason.
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
include_directories(${JSONCPP_INCLUDE_DIRS})

find_package(jsoncpp REQUIRED)

if (DO_TESTS)

    # add_subdirectory(tests)
    add_subdirectory(sandbox)

else()

    # Include SWIG module
    set_source_files_properties(wrapper.i PROPERTIES CPLUSPLUS ON)

    # Add SWIG Java module
    swig_add_library(game_java LANGUAGE java SOURCES wrapper.i ${SOURCES})
    target_link_libraries(game_java jsoncpp_lib)

    # Add SWIG CSharp module
    swig_add_library(game_csharp LANGUAGE csharp SOURCES wrapper.i ${SOURCES})
    target_link_libraries(game_csharp jsoncpp_lib)

    # Doesn't work on Windows.
    # swig_add_library(game_python LANGUAGE python SOURCES wrapper.i ${SOURCES})
    # target_link_libraries(game_python jsoncpp_lib)

    # Add SWIG JavaScript module
    # Can't get node-gyp or cmake-js to work.
    # set_source_files_properties(wrapper.i PROPERTIES SWIG_FLAGS "-node")
    # swig_add_library(game_js LANGUAGE javascript SOURCES wrapper.i ${SOURCES})
    # target_include_directories(game_js PRIVATE ${CMAKE_JS_INC})
    # target_link_libraries(game_js ${CMAKE_JS_LIB} jsoncpp_lib)

endif()
