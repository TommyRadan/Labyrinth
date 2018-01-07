#pragma once

#include <Infrastructure/Component.hpp>

namespace PhysicsEngine
{
	class Context : public Component
	{
		Context() = default;

	public:
		static Context* GetInstance();

		void Init() final;
		void Quit() final;
	};
}
