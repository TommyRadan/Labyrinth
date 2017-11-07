#include <RenderingEngine/Renderer.hpp>

namespace RenderingEngine::Renderers
{
    class BasicRenderer : public Renderer
    {
        BasicRenderer();

    public:
        static BasicRenderer* GetInstance();

        ~BasicRenderer();
    };
}
