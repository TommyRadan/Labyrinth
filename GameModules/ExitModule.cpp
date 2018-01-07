#include <Infrastructure/GameModule.hpp>

static void OnKeyDown(EventProcessing::KeyCode keyCode)
{
    if (keyCode == EventProcessing::KeyCode::ESCAPE)
    {
        EventProcessing::Context::GetInstance()->RequestQuit();
    }
}

GAME_MODULE()
{
	REGISTER_CALLBACK(OnKeyDown, OnKeyDown);
    return true;
}
