#include <RenderingEngine/Mesh/Mesh.hpp>

namespace RenderingEngine
{
	void Mesh::UploadOBJ(const std::vector<Vertex>& v)
	{
		m_Vertices = v;
	}

	const Vertex* Mesh::Vertices() const
	{
		return &m_Vertices[0];
	}

	std::size_t Mesh::VertexCount() const
	{
		return m_Vertices.size();
	}
}
