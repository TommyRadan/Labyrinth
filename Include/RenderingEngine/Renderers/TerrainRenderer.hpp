#pragma once

#include <RenderingEngine/Renderers/Renderer.hpp>

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
