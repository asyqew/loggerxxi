# CMakeLists.txt — Build configuration for Clixxi (header-only C++ CLI framework)
# This file is used to compile examples and tests.
# The library itself is header-only, so no separate library target is built.

# Minimum required CMake version (modern C++ features support)
cmake_minimum_required(VERSION 3.14)

# Project name, version, and language
project(Loggerxxi
    VERSION 0.1.0
    DESCRIPTION "A header-only C++ logger"
    HOMEPAGE_URL "https://github.com/asyqew/loggerxxi"
    LANGUAGES CXX
)

# Set C++ standard: C++17 (widely supported and sufficient for most use cases)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Use only standard C++, not compiler extensions

# Enable warnings for better code quality (recommended for development)
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(loggerxxi INTERFACE)
target_include_directories(loggerxxi
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
target_compile_features(loggerxxi INTERFACE cxx_std_17)

include(GNUInstallDirs)
install(
    TARGETS loggerxxi
    EXPORT loggerxxiTargets
)
install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
    EXPORT loggerxxiTargets
    FILE loggerxxiConfig.cmake
    NAMESPACE loggerxxi::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/loggerxxi
)

# --- Examples ---
# Build example applications to demonstrate how to use Clixxi

add_executable(example_hello examples/01_hello.cpp)
target_link_libraries(example_hello PRIVATE loggerxxi)

add_executable(example_advanced examples/02_advanced.cpp)
target_link_libraries(example_advanced PRIVATE loggerxxi)
