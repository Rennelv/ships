cmake_minimum_required(VERSION 3.28)
project(SeaBattle LANGUAGES CXX)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option to build shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Create compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include FetchContent module
include(FetchContent)

# Check if SFML is available locally
find_package(SFML 2.6 COMPONENTS graphics window system audio QUIET)

if (NOT SFML_FOUND)
    message(WARNING "SFML not found locally. Fetching from GitHub...")
    # Fetch SFML from GitHub if not found locally
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
    )
    FetchContent_MakeAvailable(SFML)
endif()

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Add executable target
add_executable(SeaBattle ${SOURCES})

# Link SFML libraries
if (SFML_FOUND)
    target_link_libraries(SeaBattle PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
else()
    target_link_libraries(SeaBattle PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
endif()

# Set C++ standard to C++17
target_compile_features(SeaBattle PRIVATE cxx_std_17)

# Add debug-specific compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra -pedantic")

# Windows-specific command to copy OpenAL DLL
if(WIN32)
    add_custom_command(
        TARGET SeaBattle
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
        $<TARGET_FILE_DIR:SeaBattle>
        VERBATIM
    )
endif()