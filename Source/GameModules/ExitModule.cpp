#include <Infrastructure/GameModule.hpp>
#include <EventProcessing/EventHandler.hpp>
#include <EventProcessing/EventProcessing.hpp>

void OnKeyDown(EventProcessing::KeyCode keyCode)
{
    if (keyCode == EventProcessing::KeyCode::ESCAPE)
    {
        EventProcessing::Context::GetInstance()->RequestQuit();
    }
}

bool ModuleInit()
{
    EventProcessing::EventHandler::GetInstance()->RegisterOnKeyDownCallback(OnKeyDown);
    return true;
}
