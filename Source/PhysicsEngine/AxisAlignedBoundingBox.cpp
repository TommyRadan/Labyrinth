#include <PhysicsEngine\AxisAlignedBoundingBox.hpp>

PhysicsEngine::AxisAlignedBoundingBox::AxisAlignedBoundingBox(const float minX, const float minY, const float minZ, const float maxX, const float maxY, const float maxZ)
	: m_MinX{ minX }, m_MinY{ minY }, m_MinZ{ minZ }, m_MaxX{ maxX }, m_MaxY{ maxY }, m_MaxZ{ maxZ }
{}

const bool PhysicsEngine::AxisAlignedBoundingBox::IsInCollision(glm::vec3 point)
{
	if (point.x <= m_MinX - 0.2f || point.x >= m_MaxX + 0.2f)
	{
		return false;
	}

	if (point.y <= m_MinY - 0.2f || point.y >= m_MaxY + 0.2f)
	{
		return false;
	}

	if (point.z <= m_MinZ - 0.2f || point.z >= m_MaxZ + 0.2f)
	{
		return false;
	}

	return true;
}
