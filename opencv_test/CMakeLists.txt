

include_directories(/usr/local/Cellar/opencv/4.5.4/include/opencv4/)
link_directories(/usr/local/Cellar/opencv/4.5.4/lib/)

add_executable(test11 test11.cpp)

# add libs you need
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
# linking
target_link_libraries(test11 ${OpenCV_LIBS})
