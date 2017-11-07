#pragma once

#include <RenderingEngine/Renderer.hpp>

namespace RenderingEngine::Renderers
{
    class TerrainRenderer : public Renderer
    {
        TerrainRenderer();

    public:
        static TerrainRenderer* GetInstance();

        ~TerrainRenderer();
    };
}
