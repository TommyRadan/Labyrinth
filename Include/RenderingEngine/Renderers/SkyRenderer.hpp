#pragma once

#include <RenderingEngine/Renderers/Renderer.hpp>

namespace RenderingEngine::Renderers
{
    class SkyRenderer : public Renderer
    {
        SkyRenderer();

    public:
        static SkyRenderer* GetInstance();

        ~SkyRenderer();
    };
}
