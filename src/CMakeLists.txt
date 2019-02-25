add_executable(raspimage main.cpp)
target_link_libraries(raspimage ${OpenCV_LIBS} )

add_executable(display main_display.cpp)
target_link_libraries(display ${OpenCV_LIBS} )

add_subdirectory(compression)
