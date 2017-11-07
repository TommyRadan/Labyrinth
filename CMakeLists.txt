cmake_minimum_required(VERSION 3.2)
project(Labyrinth)

set(CMAKE_CXX_STANDARD 17)
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
        UPDATE_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
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
        Include/EventProcessing/EventHandler.hpp
        Include/RenderingEngine/Image/Image.hpp
        Include/RenderingEngine/Image/StbImageLoader.hpp
        Include/RenderingEngine/Mesh/Mesh.hpp
        Include/RenderingEngine/Mesh/ObjLoader.hpp
        Include/RenderingEngine/Mesh/Vertex.hpp
        Include/RenderingEngine/Mesh/TerrainGenerator.hpp
        Include/RenderingEngine/OpenGL/Color.hpp
        Include/RenderingEngine/OpenGL/Framebuffer.hpp
        Include/RenderingEngine/OpenGL/OpenGL.hpp
        Include/RenderingEngine/OpenGL/Program.hpp
        Include/RenderingEngine/OpenGL/Shader.hpp
        Include/RenderingEngine/OpenGL/Texture.hpp
        Include/RenderingEngine/OpenGL/Typedef.hpp
        Include/RenderingEngine/OpenGL/VertexArray.hpp
        Include/RenderingEngine/OpenGL/VertexBuffer.hpp
        Include/RenderingEngine/Renderers/BasicRenderer.hpp
        Include/RenderingEngine/Renderers/TerrainRenderer.hpp
        Include/RenderingEngine/Window.hpp
        Include/RenderingEngine/Camera.hpp
        Include/RenderingEngine/Model.hpp
        Include/RenderingEngine/Renderable.hpp
        Include/RenderingEngine/RenderOptions.hpp
        Include/RenderingEngine/Renderer.hpp
        Include/Infrastructure/Component.hpp
        Include/Infrastructure/Exception.hpp
        Include/Infrastructure/GameModule.hpp
        Include/Infrastructure/Settings.hpp
        Include/Labyrinth/Labyrinth.hpp)

# Define source files
set(LABYRINTH_SOURCE_FILES
        Source/EventProcessing/EventProcessing.cpp
        Source/EventProcessing/EventHandler.cpp
        Source/RenderingEngine/Image/Image.cpp
        Source/RenderingEngine/Image/StbImageLoader.cpp
        Source/RenderingEngine/Mesh/Mesh.cpp
        Source/RenderingEngine/Mesh/ObjLoader.cpp
        Source/RenderingEngine/Mesh/TerrainGenerator.cpp
        Source/RenderingEngine/OpenGL/Framebuffer.cpp
        Source/RenderingEngine/OpenGL/OpenGL.cpp
        Source/RenderingEngine/OpenGL/Program.cpp
        Source/RenderingEngine/OpenGL/Shader.cpp
        Source/RenderingEngine/OpenGL/Texture.cpp
        Source/RenderingEngine/OpenGL/VertexArray.cpp
        Source/RenderingEngine/OpenGL/VertexBuffer.cpp
        Source/RenderingEngine/Renderers/BasicRenderer.cpp
        Source/RenderingEngine/Renderers/TerrainRenderer.cpp
        Source/RenderingEngine/Window.cpp
        Source/RenderingEngine/Camera.cpp
        Source/RenderingEngine/Model.cpp
        Source/RenderingEngine/Renderable.cpp
        Source/RenderingEngine/Renderer.cpp
        Source/Infrastructure/Component.cpp
        Source/Infrastructure/Exception.cpp
        Source/Infrastructure/Settings.cpp
        Source/Labyrinth/Labyrinth.cpp)

# Define game modules
set(LABYRINTH_GAME_MODULES
        GameModules/CameraModule.cpp
        GameModules/ExitModule.cpp)

# Define main executable
add_executable(Labyrinth
        ${LABYRINTH_HEADER_FILES}
        ${LABYRINTH_SOURCE_FILES}
        ${LABYRINTH_GAME_MODULES}
        Source/Control/MainLoop.cpp)

# Add dependencies
add_dependencies(Labyrinth glm)

# Link internal and external libraries
target_link_libraries(Labyrinth ${SDL2_LIBRARY})
target_link_libraries(Labyrinth ${GLEW_LIBRARY})
target_link_libraries(Labyrinth ${OPENGL_LIBRARIES})
