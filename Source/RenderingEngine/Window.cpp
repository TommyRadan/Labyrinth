#include <RenderingEngine/Window.hpp>
#include <SDL2/SDL.h>
#include <Control/Settings.hpp>
#include <Infrastructure/Exception.hpp>

namespace RenderingEngine
{
    Window::Window() :
            m_Window { nullptr },
            m_GlContext { nullptr }
    {}

    void Window::Init()
    {
        Settings* settings = Settings::GetInstance();
        uint32_t window_flags = SDL_WINDOW_OPENGL;
        WinType type = settings->GetWindowType();

        if (type == WinType::WIN_TYPE_BORDERLESS)
        {
            window_flags |= SDL_WINDOW_BORDERLESS;
        }

        if (type == WinType::WIN_TYPE_FULLSCREEN)
        {
            window_flags |= SDL_WINDOW_FULLSCREEN;
        }

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, settings->IsDoubleBuffered()?1:0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_Window = SDL_CreateWindow(
                settings->GetWindowName(),
                SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED,
                settings->GetWindowWidth(),
                settings->GetWindowHeight(),
                window_flags
        );

        if (m_Window == nullptr)
        {
            throw Exception(SDL_GetError());
        }

        m_GlContext = SDL_GL_CreateContext((SDL_Window*) m_Window);
    }

    void Window::Quit()
    {
        SDL_GL_DeleteContext(m_GlContext);
        SDL_DestroyWindow((SDL_Window*) m_Window);
    }

    void Window::SwapBuffers()
    {
        SDL_GL_SwapWindow((SDL_Window*) m_Window);
    }

    void Window::ShowMessage(const std::string& title, const std::string& message)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), (SDL_Window*) m_Window);
    }
}
