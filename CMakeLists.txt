cmake_minimum_required(VERSION 3.20)

# Project definition
project(czar
    VERSION 0.1.0
    DESCRIPTION "Czar Programming Language Compiler"
    LANGUAGES CXX
)

# Set C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Platform-specific settings
if(MSVC)
    # MSVC-specific flags
    add_compile_options(
        /W4                 # Warning level 4
        /permissive-        # Standards conformance mode
        /Zc:__cplusplus     # Enable updated __cplusplus macro
    )
    # Enable C++23 features for MSVC
    # Note: MSVC uses /std:c++latest for C++23 as /std:c++23 is not yet available
    add_compile_options(/std:c++latest)
else()
    # GCC/Clang flags
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include subdirectories
add_subdirectory(src)
