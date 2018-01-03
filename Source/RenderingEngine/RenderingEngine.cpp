#include <RenderingEngine/RenderingEngine.hpp>
#include <RenderingEngine/Window.hpp>
#include <RenderingEngine/OpenGL/OpenGL.hpp>

#include <RenderingEngine\Renderers\TexturedRenderer.hpp>

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

    RenderingEngine::OpenGL::Context::GetInstance()->Enable(RenderingEngine::OpenGL::Capability::CullFace);
    RenderingEngine::OpenGL::Context::GetInstance()->Enable(RenderingEngine::OpenGL::Capability::DepthTest);
}

void RenderingEngine::Context::Quit()
{
    RenderingEngine::OpenGL::Context::GetInstance()->Quit();
    RenderingEngine::Window::GetInstance()->Quit();
}

void  RenderingEngine::Context::AddRenderable(Renderable* renderable)
{
	m_Renderables.push_back(renderable);
}

void RenderingEngine::Context::Render()
{
    RenderingEngine::Window::GetInstance()->Clear();

	RenderingEngine::Renderers::TexturedRenderer::GetInstance()->StartRenderer();
	RenderingEngine::Renderers::TexturedRenderer::GetInstance()->SetupCamera();

    for (auto& renderable : m_Renderables)
	{
		renderable->Render();
	}

	RenderingEngine::Renderers::TexturedRenderer::GetInstance()->StopRenderer();

    RenderingEngine::Window::GetInstance()->SwapBuffers();
}
