#include <EventProcessing/EventProcessing.hpp>
#include <RenderingEngine/Window.hpp>
#include <Infrastructure/Exception.hpp>
#include <RenderingEngine/OpenGL/OpenGL.hpp>
#include <EventProcessing/EventHandler.hpp>

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    try
    {
        EventProcessing::Context::GetInstance()->Init();
        RenderingEngine::Window::GetInstance()->Init();
        RenderingEngine::OpenGL::Context::GetInstance()->Init();
    }
    catch (const Exception& e)
    {
        RenderingEngine::Window::GetInstance()->ShowMessage("Initialization Error", e.what());
        return EXIT_FAILURE;
    }

    try
    {
        for (;;)
        {
            RenderingEngine::Window::GetInstance()->Clear();
            EventProcessing::EventHandler::GetInstance()->HandleEvents();

            /**
             * TODO: Render the scene here.
             */

            RenderingEngine::Window::GetInstance()->SwapBuffers();

            if (EventProcessing::Context::GetInstance()->IsQuitRequested()) break;
        }
    }
    catch (const Exception& e)
    {
        RenderingEngine::Window::GetInstance()->ShowMessage("Error", e.what());
        return EXIT_FAILURE;
    }

    RenderingEngine::OpenGL::Context::GetInstance()->Quit();
    RenderingEngine::Window::GetInstance()->Quit();
    EventProcessing::Context::GetInstance()->Quit();
    return EXIT_SUCCESS;
}
