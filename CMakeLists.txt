cmake_minimum_required(VERSION 3.20)
project(raspimage)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
# Include Boost as an imported target
find_package(Boost REQUIRED)
IF (Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
  ADD_DEFINITIONS("-DHAS_BOOST")
ENDIf()
find_package(OpenCV REQUIRED)
find_package(websocketpp REQUIRED)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate


enable_testing()
add_subdirectory(tests)
add_subdirectory(src)

