add_executable(camera2shm main.cpp)
target_link_libraries(camera2shm ${OpenCV_LIBS} ${Boost_LIBS} rt pthread)

add_subdirectory(compression)
