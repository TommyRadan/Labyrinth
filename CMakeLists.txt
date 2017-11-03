cmake_minimum_required(VERSION 3.2)
project(Labyrinth)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

# Find external dependencies
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# GLM
include(ExternalProject)
ExternalProject_Add(glm
        PREFIX ${CMAKE_BINARY_DIR}/glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG master
        INSTALL_COMMAND "")
ExternalProject_Get_Property(glm source_dir)

# Include directories
include_directories(Include/)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${source_dir}/glm)

# Define header files
set(LABYRINTH_HEADER_FILES
        Include/EventProcessing/EventProcessing.hpp
        Include/RenderingEngine/Window.hpp
        Include/RenderingEngine/Camera.hpp
        Include/Infrastructure/Component.hpp
        Include/Infrastructure/Exception.hpp
        Include/Infrastructure/Settings.hpp)

# Define source files
set(LABYRINTH_SOURCE_FILES
        Source/EventProcessing/EventProcessing.cpp
        Source/RenderingEngine/Window.cpp
        Source/RenderingEngine/Camera.cpp
        Source/Infrastructure/Component.cpp
        Source/Infrastructure/Exception.cpp
        Source/Infrastructure/Settings.cpp)

# Define main executable
add_executable(Labyrinth
        ${LABYRINTH_HEADER_FILES}
        ${LABYRINTH_SOURCE_FILES}
        Source/Control/MainLoop.cpp)

# Add dependencies
add_dependencies(Labyrinth glm)

# Link internal and external libraries
target_link_libraries(Labyrinth ${SDL2_LIBRARY})
target_link_libraries(Labyrinth ${GLEW_LIBRARY})
target_link_libraries(Labyrinth ${OPENGL_LIBRARIES})
