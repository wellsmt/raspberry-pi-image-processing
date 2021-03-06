# Define library. Only source files here!
cmake_minimum_required(VERSION 3.7)
project(libcompression VERSION 0.1 LANGUAGES CXX)

add_library(compression INTERFACE)

target_include_directories(compression INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>)

# 'make install' to the correct locations (provided by GNUInstallDirs).
install(TARGETS compression EXPORT MyLibraryConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT MyLibraryConfig DESTINATION share/MyLibrary/cmake)

# This makes the project importable from the build directory
export(TARGETS compression FILE MyLibraryConfig.cmake)

# Every library has unit tests, of course
add_executable(testcompression
    tests/compression_test.cpp
    tests/histogram_test.cpp)

target_link_libraries(testcompression
    compression
    gtest
    gmock_main)

add_test(testcompression testcompression)
