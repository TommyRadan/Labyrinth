#include <EventProcessing/EventProcessing.hpp>
#include <Infrastructure/Exception.hpp>
#include <EventProcessing/EventHandler.hpp>
#include <RenderingEngine/RenderingEngine.hpp>
#include <PhysicsEngine/PhysicsEngine.hpp>

#include <RenderingEngine/Window.hpp>

int main(int argc, char* argv[])
{
    (void) argc;
    (void) argv;

    try
    {
        EventProcessing::Context::GetInstance()->Init();
        RenderingEngine::Context::GetInstance()->Init();
		PhysicsEngine::Context::GetInstance()->Init();
    }
    catch (const Exception& e)
    {
        RenderingEngine::Window::GetInstance()->ShowMessage("Initialization Error", e.what());
        return EXIT_FAILURE;
    }

	EventProcessing::EventHandler::GetInstance()->DispatchOnGameStartCallback();

    try
    {
        for (;;)
        {
            EventProcessing::EventHandler::GetInstance()->HandleEvents();
			PhysicsEngine::Context::GetInstance()->Process();
            RenderingEngine::Context::GetInstance()->Render();

            if (EventProcessing::Context::GetInstance()->IsQuitRequested()) break;
        }
    }
    catch (const Exception& e)
    {
        RenderingEngine::Window::GetInstance()->ShowMessage("Error", e.what());
        return EXIT_FAILURE;
    }

	EventProcessing::EventHandler::GetInstance()->DispatchOnGameEndCallback();

	PhysicsEngine::Context::GetInstance()->Quit();
    RenderingEngine::Context::GetInstance()->Quit();
    EventProcessing::Context::GetInstance()->Quit();
    return EXIT_SUCCESS;
}
