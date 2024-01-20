cmake_minimum_required(VERSION 3.25)  
project(demo)  
set(CMAKE_CXX_STANDARD 17)  

file(GLOB RESOURCE_FILES LIST_DIRECTORIES TRUE "${CMAKE_CURRENT_SOURCE_DIR}/*.png")

file(COPY ${RESOURCE_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(demo_01 main.cpp)

target_link_libraries(demo_01 ${OpenCV_LIBS})