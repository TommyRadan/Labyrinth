#pragma once

#include <Infrastructure/Component.hpp>
#include <PhysicsEngine/AxisAlignedBoundingBox.hpp>
#include <vector>
#include <glm.hpp>

namespace PhysicsEngine
{
	class Context : public Component
	{
		Context() = default;

	public:
		static Context* GetInstance();

		void Init() final;
		void Quit() final;

		void Process();

		void AddAABB(const PhysicsEngine::AxisAlignedBoundingBox& aabb);

	private:
		glm::vec3 m_LastCamPosition;
		glm::vec3 m_CurrentCamPosition;

		std::vector<PhysicsEngine::AxisAlignedBoundingBox> m_AABBs;

		bool isColliding();
	};
}
