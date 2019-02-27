add_executable(raspimage main.cpp)
target_link_libraries(raspimage ${OpenCV_LIBS} )

add_executable(echoserver web_socket.cpp)
add_subdirectory(compression)
