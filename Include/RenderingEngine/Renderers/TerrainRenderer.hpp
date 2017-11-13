#pragma once

#include <RenderingEngine/Renderers/Renderer.hpp>

namespace RenderingEngine
{
    namespace Renderers
    {
        class TerrainRenderer : public Renderer
        {
            TerrainRenderer();

        public:
            static TerrainRenderer* GetInstance();

            ~TerrainRenderer();
        };
    }
}
