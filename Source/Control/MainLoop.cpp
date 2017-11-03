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
        return -1;
    }

    try
    {
        for (;;)
        {
            EventProcessing::GetInstance()->Process();
            EventProcessing::GetInstance()->Update();

            RenderingEngine::Window::GetInstance()->SwapBuffers();

            if (EventProcessing::GetInstance()->IsQuitRequested()) break;
        }
    }
    catch (const Exception& e)
    {
        RenderingEngine::Window::GetInstance()->ShowMessage("Error", e.what());
        return -1;
    }

    RenderingEngine::Window::GetInstance()->Quit();
    EventProcessing::GetInstance()->Quit();
    return 0;
}
