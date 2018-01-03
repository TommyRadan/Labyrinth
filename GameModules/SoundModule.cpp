#include <Infrastructure/GameModule.hpp>

static void OnGameStart()
{
	/*
	 * TODO: Load and start the sound!
	 */
}

static void OnGameEnd()
{
	/*
	 * TODO: Stop and unload the sound!
	 */
}

bool ModuleInit()
{
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameStart);
	return true;
}
