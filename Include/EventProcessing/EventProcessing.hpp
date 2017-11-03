#pragma once

#include <Infrastructure/Component.hpp>

class EventProcessing : public Component
{
    EventProcessing();

public:
    static EventProcessing* GetInstance();

	void Init() final;
	void Quit() final;

	void Process();
	void Update();

    const bool IsQuitRequested() const;

private:
	bool m_IsUserQuit;
};
