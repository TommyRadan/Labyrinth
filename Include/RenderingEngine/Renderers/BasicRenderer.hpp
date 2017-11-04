#include <RenderingEngine/Renderer.hpp>

namespace RenderingEngine::Renderers
{
    struct BasicRenderer : public Renderer
    {
        BasicRenderer();
        ~BasicRenderer();

        void SetupCamera() final;
    };
}
