cmake_minimum_required(VERSION 3.19)
project(opencli)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib)

# Include OpenCV
find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencli
        lib/cli.cpp
        lib/cli.hpp
        src/main.cc lib/imgproc.cpp lib/imgproc.hpp lib/virtualpainter.cpp lib/virtualpainter.h lib/facedetection.cpp lib/facedetection.h)

target_link_libraries(opencli ${OpenCV_LIBS})
