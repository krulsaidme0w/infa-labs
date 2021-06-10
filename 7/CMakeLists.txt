cmake_minimum_required(VERSION 3.1.0)

project(lab7)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(lab7 main.cpp)

target_link_libraries(lab7 Qt5::Widgets)