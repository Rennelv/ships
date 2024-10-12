cmake_minimum_required(VERSION 3.28)
project(SeaBattle LANGUAGES CXX)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Add executable target
add_executable(SeaBattle ${SOURCES})

# Set C++ standard to C++17
target_compile_features(SeaBattle PRIVATE cxx_std_17)

