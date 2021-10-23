cmake_minimum_required(VERSION 3.10)

# set the project name
project(Picross)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES
    src/*.h
    src/*.cpp
)

# add the executable
add_executable(Picross ${SOURCES})
target_link_libraries(Picross ${SDL2_LIBRARIES})

#set(CMAKE_BUILD_TYPE Debug)

