#pragma once

#include <EventProcessing/EventHandler.hpp>
#include <EventProcessing/EventProcessing.hpp>

#define GAME_MODULE() bool ModuleInit()
#define REGISTER_CALLBACK(event, callback) EventProcessing::EventHandler::GetInstance()->Register ## event ## Callback(callback);

static bool ModuleInit();

static bool initStatus = ModuleInit();
