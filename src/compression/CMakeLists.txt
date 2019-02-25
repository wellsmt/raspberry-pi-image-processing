# Define library. Only source files here!
project(libcompression VERSION 0.1 LANGUAGES CXX)

add_library(compression INTERFACE)

target_include_directories(compression INTERFACE include/)

# Depend on a library that we defined in the top-level file
#target_link_libraries(compression
#    boost)

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
    tests/testcompression.cpp
    tests/histogram_test.cpp)

target_link_libraries(testcompression
    compression
    gtest
    gmock_main)

add_test(testcompression testcompression)
