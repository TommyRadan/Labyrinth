#include <PhysicsEngine/PhysicsEngine.hpp>
#include <RenderingEngine/Camera.hpp>
#include <iostream>

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

void PhysicsEngine::Context::Process()
{
	bool isInCollision = false;

	for (auto& aabb : m_AABBs)
	{
		if (aabb.IsInCollision(RenderingEngine::Camera::GetInstance()->GetPosition()))
		{
			isInCollision = true;
			break;
		}
	}

	if (isInCollision)
	{
		//std::cout << "Collision" << std::endl;
		RenderingEngine::Camera::GetInstance()->SetPosition(m_LastCamPosition);
	}

	m_LastCamPosition = RenderingEngine::Camera::GetInstance()->GetPosition();
}

void PhysicsEngine::Context::AddAABB(const PhysicsEngine::AxisAlignedBoundingBox& aabb)
{
	m_AABBs.push_back(aabb);
}
