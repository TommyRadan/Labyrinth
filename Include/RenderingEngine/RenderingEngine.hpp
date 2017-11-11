#pragma once

#include <RenderingEngine/Window.hpp>
#include <RenderingEngine/Renderer.hpp>
#include <RenderingEngine/Renderable.hpp>
#include <RenderingEngine/Renderables/Model.hpp>
#include <RenderingEngine/Renderables/Terrain.hpp>
#include <RenderingEngine/Camera.hpp>
#include <RenderingEngine/Image/Image.hpp>
#include <RenderingEngine/Image/StbImageLoader.hpp>
#include <RenderingEngine/Mesh/Mesh.hpp>
#include <RenderingEngine/Mesh/ObjLoader.hpp>
#include <RenderingEngine/Mesh/TerrainGenerator.hpp>
#include <RenderingEngine/OpenGL/OpenGL.hpp>
#include <RenderingEngine/Renderers/BasicRenderer.hpp>
#include <RenderingEngine/Renderers/TerrainRenderer.hpp>

#include <Infrastructure/Component.hpp>

namespace RenderingEngine
{
    class Context : public Component
    {
        Context() = default;

    public:
        static Context* GetInstance();

        void Init() final;
        void Quit() final;

        void Render();
    };
}
