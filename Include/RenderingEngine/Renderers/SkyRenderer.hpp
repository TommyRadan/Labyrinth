#pragma once

#include <RenderingEngine/Renderer.hpp>

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
