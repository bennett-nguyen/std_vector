cmake_minimum_required(VERSION 4.3)
project(STD_VECTOR)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)

include_directories(./)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})