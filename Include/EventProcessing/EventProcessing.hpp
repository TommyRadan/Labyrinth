#pragma once

#include <Infrastructure/Component.hpp>

namespace EventProcessing
{
	class Context : public Component
	{
		Context();

	public:
		static Context* GetInstance();

		void Init() final;
		void Quit() final;

		void RequestQuit();
		const bool IsQuitRequested() const;

	private:
		bool m_IsQuitRequested;
	};
}
