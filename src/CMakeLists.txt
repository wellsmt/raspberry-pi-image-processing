add_executable(raspimage main.cpp)
target_link_libraries(raspimage ${OpenCV_LIBS} ${Boost_LIBS} rt pthread)

add_subdirectory(compression)
