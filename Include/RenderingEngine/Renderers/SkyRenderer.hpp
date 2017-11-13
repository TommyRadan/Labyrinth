#pragma once

#include <RenderingEngine/Renderers/Renderer.hpp>

namespace RenderingEngine
{
    namespace Renderers
    {
        class SkyRenderer : public Renderer
        {
            SkyRenderer();

        public:
            static SkyRenderer* GetInstance();

            ~SkyRenderer();
        };
    }
}
