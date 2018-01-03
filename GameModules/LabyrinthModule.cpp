#include <Infrastructure/GameModule.hpp>

static void OnGameStart()
{
	/*
	 * TODO: Spawn the world!
	 */
}

static void OnGameEnd()
{
	/*
	 * TODO: Destroy the world!
	 */
}

bool ModuleInit()
{
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameStartCallback(OnGameStart);
	EventProcessing::EventHandler::GetInstance()->RegisterOnGameEndCallback(OnGameStart);
	return true;
}
