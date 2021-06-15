add_executable(camera2shm main.cpp)
target_link_libraries(camera2shm ${OpenCV_LIBS} ${Boost_LIBS} rt pthread)

add_executable(websocket_server main_websocket_server.cpp)
target_link_libraries(websocket_server ${Boost_LIBS} rt pthread)

add_executable(testCamera2shm
    main_test.cpp)

target_link_libraries(testCamera2shm
  ${OpenCV_LIBS}
  gtest
  gmock_main)

add_test(testCamera2shm testCamera2shm)

add_subdirectory(compression)
