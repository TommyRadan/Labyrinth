#include <PhysicsEngine/PhysicsEngine.hpp>
#include <RenderingEngine/Camera.hpp>

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
	m_CurrentCamPosition = RenderingEngine::Camera::GetInstance()->GetPosition();

	if (!isColliding())
	{
		goto end;
	}

	RenderingEngine::Camera::GetInstance()->SetPosition({ m_CurrentCamPosition.x, m_LastCamPosition.y, m_CurrentCamPosition.z });

	if (!isColliding())
	{
		goto end;
	}

	RenderingEngine::Camera::GetInstance()->SetPosition({ m_LastCamPosition.x, m_CurrentCamPosition.y, m_CurrentCamPosition.z });

	if (!isColliding())
	{
		goto end;
	}

	RenderingEngine::Camera::GetInstance()->SetPosition({ m_LastCamPosition.x, m_LastCamPosition.y, m_CurrentCamPosition.z });

	if (!isColliding())
	{
		goto end;
	}

	RenderingEngine::Camera::GetInstance()->SetPosition(m_LastCamPosition);

	end:
	m_LastCamPosition = RenderingEngine::Camera::GetInstance()->GetPosition();
}

void PhysicsEngine::Context::AddAABB(const PhysicsEngine::AxisAlignedBoundingBox& aabb)
{
	m_AABBs.push_back(aabb);
}

bool PhysicsEngine::Context::isColliding()
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

	return isInCollision;
}
