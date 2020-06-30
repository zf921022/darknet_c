cmake_minimum_required(VERSION 3.14)

project(yolo)
include_directories(/usr/local/include/opencv4)
include_directories(/usr/local/cuda/include)

link_directories(/home/zf/darknet_c/src/)
link_directories(/home/zf/darknet_c/)
link_directories(/usr/local/lib)

link_directories(/usr/local/cuda/lib64)


add_executable(yolo src/main.cpp src/imgprocess.cpp src/Yolov4Infer.cpp)

target_link_libraries(yolo cudart)
target_link_libraries(yolo libdarknet.so)
target_link_libraries(yolo opencv_core)
target_link_libraries(yolo opencv_highgui)
target_link_libraries(yolo opencv_imgcodecs)
target_link_libraries(yolo opencv_imgproc)
target_link_libraries(yolo opencv_videoio)