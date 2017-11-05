#include <EventProcessing/EventProcessing.hpp>
#include <SDL2/SDL.h>
#include <Infrastructure/Exception.hpp>

EventProcessing::Context::Context() :
    m_IsQuitRequested { false }
{}

EventProcessing::Context* EventProcessing::Context::GetInstance()
{
    static Context* instance { nullptr };

    if (instance == nullptr)
    {
        instance = new Context();
    }

    return instance;
}

void EventProcessing::Context::Init()
{
	if (m_IsInitialized)
	{
		throw Exception("EventProcessing second initialization attempt");
	}

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        throw Exception("Could not initialize event system");
    }

    m_IsInitialized = true;
}

void EventProcessing::Context::Quit()
{
	if (!m_IsInitialized)
    {
        throw Exception("EventProcessing quit attempt without initialization");
	}

	SDL_QuitSubSystem(SDL_INIT_VIDEO);

    m_IsInitialized = false;
}

void EventProcessing::Context::RequestQuit()
{
    m_IsQuitRequested = true;
}

const bool EventProcessing::Context::IsQuitRequested() const
{
    return m_IsQuitRequested;
}
