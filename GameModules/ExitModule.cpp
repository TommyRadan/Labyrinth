#include <Infrastructure/GameModule.hpp>

static void OnKeyDown(EventProcessing::KeyCode keyCode)
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
