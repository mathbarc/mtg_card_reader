cmake_policy(SET CMP0048 NEW)

project("MTG Card Reader" VERSION 0.0.1)
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV COMPONENTS core highgui flann imgcodecs imgproc REQUIRED)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH "Include dir")

list(APPEND PROJECT_INCLUDE_DIRS 
            ${INCLUDE_DIR})

include_directories(${PROJECT_INCLUDE_DIRS})

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

add_executable("card_reader" ${SOURCES} ${HEADERS})
 target_link_libraries("card_reader" ${OpenCV_LIBRARIES})
