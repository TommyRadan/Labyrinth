#include <EventProcessing/EventProcessing.hpp>
#include <RenderingEngine/Window.hpp>
#include <Infrastructure/Exception.hpp>

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    try
    {
        EventProcessing::GetInstance()->Init();
        RenderingEngine::Window::GetInstance()->Init();
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

            EventProcessing::GetInstance()->Process();
            EventProcessing::GetInstance()->Update();

            /**
             * TODO: Render the scene here.
             */

            RenderingEngine::Window::GetInstance()->SwapBuffers();

            if (EventProcessing::GetInstance()->IsQuitRequested()) break;
        }
    }
    catch (const Exception& e)
    {
        RenderingEngine::Window::GetInstance()->ShowMessage("Error", e.what());
        return EXIT_FAILURE;
    }

    RenderingEngine::Window::GetInstance()->Quit();
    EventProcessing::GetInstance()->Quit();
    return EXIT_SUCCESS;
}
