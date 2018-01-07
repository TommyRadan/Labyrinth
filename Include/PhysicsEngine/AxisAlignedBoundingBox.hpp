#pragma once

#include <glm.hpp>

namespace PhysicsEngine
{
	struct AxisAlignedBoundingBox
	{
		AxisAlignedBoundingBox(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

		const bool IsInCollision(glm::vec3 point);

	private:
		float m_MinX, m_MaxX;
		float m_MinY, m_MaxY;
		float m_MinZ, m_MaxZ;
	};
}
