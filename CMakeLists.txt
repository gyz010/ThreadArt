cmake_minimum_required(VERSION 3.25)
project(ThreadArt)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics)

add_executable(ThreadArt src/main.cpp src/Canvas.cpp inc/Canvas.h src/Bresenham.cpp inc/Bresenham.h
        src/ImageTransform.cpp
        inc/ImageTransform.h
        src/LineTest.cpp
        inc/LineTest.h
)
target_link_libraries(ThreadArt sfml-graphics fftw3)