#include <RenderingEngine/RenderingEngine.hpp>

RenderingEngine::Context* RenderingEngine::Context::GetInstance()
{
    static Context* instance = nullptr;

    if (instance == nullptr)
    {
        instance = new Context;
    }

    return instance;
}

void RenderingEngine::Context::Init()
{
    RenderingEngine::Window::GetInstance()->Init();
    RenderingEngine::OpenGL::Context::GetInstance()->Init();

    RenderingEngine::OpenGL::Context::GetInstance()->Enable(RenderingEngine::OpenGL::Capability::DepthTest);
}

void RenderingEngine::Context::Quit()
{
    RenderingEngine::OpenGL::Context::GetInstance()->Quit();
    RenderingEngine::Window::GetInstance()->Quit();
}

void RenderingEngine::Context::Render()
{
    RenderingEngine::Window::GetInstance()->Clear();

    /**
     * TODO: Render the scene here.
     */

    RenderingEngine::Window::GetInstance()->SwapBuffers();
}
