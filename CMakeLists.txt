cmake_minimum_required(VERSION 3.25)  
project(demo)  
  
set(CMAKE_CXX_STANDARD 17)  
  
find_package(OpenCV REQUIRED)  
  
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
message(STATUS "OpenCV_VERSION: ${OpenCV_VERSION}")
message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")

add_subdirectory(lesson_01)
add_subdirectory(lesson_02)
add_subdirectory(lesson_03)
add_subdirectory(lesson_04)
