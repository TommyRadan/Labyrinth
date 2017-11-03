#include <EventProcessing/EventProcessing.hpp>
#include <SDL2/SDL.h>

EventProcessing::EventProcessing() :
    m_IsUserQuit { false }
{}

EventProcessing* EventProcessing::GetInstance()
{
    static EventProcessing* instance { nullptr };

    if (instance == nullptr)
    {
        instance = new EventProcessing();
    }

    return instance;
}

void EventProcessing::Init()
{
	if (m_IsInitialized)
	{
		return;
	}

	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
    {
        /**
         * TODO: Trace error that initialization failed!
         */
        return;
    }

    m_IsInitialized = true;
}

void EventProcessing::Quit()
{
	if (!m_IsInitialized)
    {
		return;
	}

	SDL_QuitSubSystem(SDL_INIT_VIDEO);

    m_IsInitialized = false;
}

void EventProcessing::Process()
{
    SDL_Event events;
    while (SDL_PollEvent(&events))
    {
        switch (events.type)
        {
            /**
             * TODO: Handle event handlers here.
             */

            case SDL_QUIT:
                m_IsUserQuit = true;
                break;

            default:
                break;
        }
    }
}

void EventProcessing::Update()
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

    /**
     * TODO: Call OnUpdate handlers.
     */
}

const bool EventProcessing::IsQuitRequested() const
{
    return m_IsUserQuit;
}
