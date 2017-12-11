cmake_minimum_required(VERSION 3.2)
project(Labyrinth)

set(CMAKE_CXX_STANDARD 11)

# Find external dependencies
if (WIN32)
    set(SDL2_INCLUDE_DIR ThirdParty/Windows/SDL2/include)
    set(GLEW_INCLUDE_DIR ThirdParty/Windows/GLEW/include)
    set(SDL2_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Windows/SDL2/lib/SDL2.lib
                     ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Windows/SDL2/lib/SDL2main.lib)
    set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Windows/GLEW/lib/glew32.lib
                     ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Windows/GLEW/lib/glew32s.lib)
    set(OPENGL_LIBRARIES opengl32.lib)
else()
    find_package(SDL2 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(OpenGL)
endif()

# Include directories
include_directories(Include/)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(ThirdParty/Agnostic/GLM/)
include_directories(ThirdParty/Agnostic/STBI/)

# Define header files
set(LABYRINTH_HEADER_FILES
        Include/EventProcessing/EventProcessing.hpp
        Include/EventProcessing/EventHandler.hpp
        Include/RenderingEngine/Image/Image.hpp
        Include/RenderingEngine/Mesh/Mesh.hpp
        Include/RenderingEngine/Mesh/ObjLoader.hpp
        Include/RenderingEngine/Mesh/Vertex.hpp
        Include/RenderingEngine/Mesh/TerrainGenerator.hpp
        Include/RenderingEngine/Renderables/Model.hpp
        Include/RenderingEngine/Renderables/Renderable.hpp
        Include/RenderingEngine/Renderables/Terrain.hpp
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
        Include/RenderingEngine/Renderers/Renderer.hpp
        Include/RenderingEngine/Renderers/SkyRenderer.hpp
        Include/RenderingEngine/Renderers/TerrainRenderer.hpp
        Include/RenderingEngine/Window.hpp
        Include/RenderingEngine/Camera.hpp
        Include/RenderingEngine/RenderOptions.hpp
        Include/RenderingEngine/RenderingEngine.hpp
        Include/Infrastructure/Component.hpp
        Include/Infrastructure/Exception.hpp
        Include/Infrastructure/GameModule.hpp
        Include/Infrastructure/Settings.hpp)

# Define source files
set(LABYRINTH_SOURCE_FILES
        Source/EventProcessing/EventProcessing.cpp
        Source/EventProcessing/EventHandler.cpp
        Source/RenderingEngine/Image/Image.cpp
        Source/RenderingEngine/Mesh/Mesh.cpp
        Source/RenderingEngine/Mesh/ObjLoader.cpp
        Source/RenderingEngine/Mesh/TerrainGenerator.cpp
        Source/RenderingEngine/Renderables/Model.cpp
        Source/RenderingEngine/Renderables/Renderable.cpp
        Source/RenderingEngine/Renderables/Terrain.cpp
        Source/RenderingEngine/OpenGL/Framebuffer.cpp
        Source/RenderingEngine/OpenGL/OpenGL.cpp
        Source/RenderingEngine/OpenGL/Program.cpp
        Source/RenderingEngine/OpenGL/Shader.cpp
        Source/RenderingEngine/OpenGL/Texture.cpp
        Source/RenderingEngine/OpenGL/VertexArray.cpp
        Source/RenderingEngine/OpenGL/VertexBuffer.cpp
        Source/RenderingEngine/Renderers/BasicRenderer.cpp
        Source/RenderingEngine/Renderers/Renderer.cpp
        Source/RenderingEngine/Renderers/SkyRenderer.cpp
        Source/RenderingEngine/Renderers/TerrainRenderer.cpp
        Source/RenderingEngine/Window.cpp
        Source/RenderingEngine/Camera.cpp
        Source/RenderingEngine/RenderingEngine.cpp
        Source/Infrastructure/Component.cpp
        Source/Infrastructure/Exception.cpp
        Source/Infrastructure/Settings.cpp)

# Define game modules
set(LABYRINTH_GAME_MODULES
        GameModules/CameraModule.cpp
        GameModules/ExitModule.cpp)

# Define Source groups
if (MSVC)
    source_group("Source\\Control" FILES Source/Control/MainLoop.cpp)
    source_group("GameModules" FILES ${LABYRINTH_GAME_MODULES})

    foreach(file ${LABYRINTH_SOURCE_FILES} ${LABYRINTH_HEADER_FILES})
        get_filename_component(GROUP ${file} PATH)
        string(REGEX REPLACE "/" "\\\\" GROUP ${GROUP})
        source_group(${GROUP} FILES ${file})
    endforeach()
endif()

# Define main executable
add_executable(Labyrinth
        ${LABYRINTH_HEADER_FILES}
        ${LABYRINTH_SOURCE_FILES}
        ${LABYRINTH_GAME_MODULES}
        Source/Control/MainLoop.cpp)

# Link internal and external libraries
target_link_libraries(Labyrinth ${SDL2_LIBRARY})
target_link_libraries(Labyrinth ${GLEW_LIBRARY})
target_link_libraries(Labyrinth ${OPENGL_LIBRARIES})
