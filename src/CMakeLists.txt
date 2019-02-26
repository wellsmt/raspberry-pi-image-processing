add_executable(raspimage main.cpp)
target_link_libraries(raspimage ${OpenCV_LIBS} )

add_subdirectory(compression)
