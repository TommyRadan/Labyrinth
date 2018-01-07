#include <PhysicsEngine/PhysicsEngine.hpp>

PhysicsEngine::Context* PhysicsEngine::Context::GetInstance()
{
	static Context* instance = nullptr;

	if (instance == nullptr)
	{
		instance = new Context;
	}

	return instance;
}

void PhysicsEngine::Context::Init()
{
}

void PhysicsEngine::Context::Quit()
{
}
