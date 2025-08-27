cmake_minimum_required(VERSION 3.23)
project(eg)

set(CMAKE_CXX_STANDARD 11)
set(ENV{OPENCV_DIR} "C:\\tools\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(eg
#        src/imgDisplay.cpp
        src/vidDisplay.cpp
        include/filter.h
        src/filter.cpp
        src/faceDetect.cpp
#        src/showFaces.cpp
        include/faceDetect.h
)

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)

target_link_libraries(eg ${OpenCV_LIBS})