#include <EventProcessing/EventHandler.hpp>
#include <EventProcessing/EventProcessing.hpp>
#include <SDL2/SDL.h>
#include <algorithm>

EventProcessing::EventHandler* EventProcessing::EventHandler::GetInstance()
{
    static EventHandler* instance = nullptr;

    if (instance == nullptr)
    {
        instance = new EventHandler;
    }

    return instance;
}

void EventProcessing::EventHandler::HandleEvents()
{
    SDL_Event events = { 0 };

    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
            case SDL_KEYDOWN:
                DispatchOnKeyDownCallback((KeyCode) events.key.keysym.sym);
                break;

            case SDL_KEYUP:
                DispatchOnKeyUpCallback((KeyCode) events.key.keysym.sym);
                break;

            case SDL_MOUSEBUTTONDOWN:
                switch(events.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        DispatchOnKeyDownCallback(KeyCode::MOUSE_LEFT);
                        break;

                    case SDL_BUTTON_RIGHT:
                        DispatchOnKeyDownCallback(KeyCode::MOUSE_RIGHT);
                        break;

                    case SDL_BUTTON_MIDDLE:
                        DispatchOnKeyDownCallback(KeyCode::MOUSE_MIDDLE);
                        break;

                    default:
                        break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch(events.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        DispatchOnKeyUpCallback(KeyCode::MOUSE_LEFT);
                        break;

                    case SDL_BUTTON_RIGHT:
                        DispatchOnKeyUpCallback(KeyCode::MOUSE_RIGHT);
                        break;

                    case SDL_BUTTON_MIDDLE:
                        DispatchOnKeyUpCallback(KeyCode::MOUSE_MIDDLE);
                        break;

                    default:
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                DispatchOnMouseMoveCallback(events.motion.xrel, events.motion.yrel);
                break;

            case SDL_QUIT:
                EventProcessing::Context::GetInstance()->RequestQuit();
                break;

            default:
                break;
        }
    }

    HandleFrame();
}

void EventProcessing::EventHandler::HandleFrame()
{
    const uint32_t ticks = SDL_GetTicks();

    static uint32_t lastTickCount = ticks;
    uint32_t deltaTime = ticks - lastTickCount;
    lastTickCount = ticks;

    // First Update will be 0, so we ignore it
    if (deltaTime == 0u)
    {
        return;
    }

    for (auto& keyCode : m_PressedKeys)
    {
        DispatchKeyPressedCallback(keyCode, deltaTime);
    }

    DispatchOnFrameCallback(deltaTime);
}

void EventProcessing::EventHandler::RegisterOnFrameCallback(std::function<void(uint32_t)> callback)
{
    m_OnFrameCallbacks.push_back(callback);
}

void EventProcessing::EventHandler::RegisterOnKeyDownCallback(std::function<void(KeyCode)> callback)
{
    m_OnKeyDownCallbacks.push_back(callback);
}

void EventProcessing::EventHandler::RegisterOnKeyUpCallback(std::function<void(KeyCode)> callback)
{
    m_OnKeyUpCallbacks.push_back(callback);
}

void EventProcessing::EventHandler::RegisterKeyPressedCallback(std::function<void(KeyCode, uint32_t)> callback)
{
    m_KeyPressedCallbacks.push_back(callback);
}

void EventProcessing::EventHandler::RegisterOnMouseMoveCallback(std::function<void(int32_t, int32_t)> callback)
{
    m_OnMouseMoveCallbacks.push_back(callback);
}

void EventProcessing::EventHandler::DispatchOnFrameCallback(uint32_t deltaTime)
{
    for (auto& callback : m_OnFrameCallbacks)
    {
        callback(deltaTime);
    }
}

void EventProcessing::EventHandler::DispatchOnKeyDownCallback(KeyCode keyCode)
{
    m_PressedKeys.erase(std::remove(m_PressedKeys.begin(), m_PressedKeys.end(), keyCode), m_PressedKeys.end());
    m_PressedKeys.push_back(keyCode);

    for (auto& callback : m_OnKeyDownCallbacks)
    {
        callback(keyCode);
    }
}

void EventProcessing::EventHandler::DispatchOnKeyUpCallback(KeyCode keyCode)
{
    m_PressedKeys.erase(std::remove(m_PressedKeys.begin(), m_PressedKeys.end(), keyCode), m_PressedKeys.end());

    for (auto& callback : m_OnKeyUpCallbacks)
    {
        callback(keyCode);
    }
}

void EventProcessing::EventHandler::DispatchKeyPressedCallback(KeyCode keyCode, uint32_t deltaTime)
{
    for (auto& callback : m_KeyPressedCallbacks)
    {
        callback(keyCode, deltaTime);
    }
}

void EventProcessing::EventHandler::DispatchOnMouseMoveCallback(int32_t deltaX, int32_t deltaY)
{
    for (auto& callback : m_OnMouseMoveCallbacks)
    {
        callback(deltaX, deltaY);
    }
}

bool EventProcessing::EventHandler::IsKeyPressed(KeyCode keyCode)
{
    auto position = std::find(m_PressedKeys.begin(), m_PressedKeys.end(), keyCode);

    return (position != m_PressedKeys.end());
}
