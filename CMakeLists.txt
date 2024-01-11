cmake_minimum_required(VERSION 3.25)
project(ThreadArt)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics)

add_executable(ThreadArt main.cpp Canvas.cpp Canvas.h Bresenham.cpp Bresenham.h
        ImageTransform.cpp
        ImageTransform.h
        LineTest.cpp
        LineTest.h
)
target_link_libraries(ThreadArt sfml-graphics fftw3)