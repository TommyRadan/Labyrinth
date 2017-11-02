cmake_minimum_required(VERSION 3.2)
project(Labyrinth)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})

add_executable(Labyrinth Source/EntryPoint.cpp)
target_link_libraries(Labyrinth ${SDL2_LIBRARY})
target_link_libraries(Labyrinth ${GLEW_LIBRARY})
target_link_libraries(Labyrinth ${OPENGL_LIBRARIES})
