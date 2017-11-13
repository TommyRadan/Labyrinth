#include <RenderingEngine/Renderables/Terrain.hpp>
#include <RenderingEngine/Mesh/TerrainGenerator.hpp>

RenderingEngine::Terrain::Terrain()
{
    RenderingEngine::Mesh mesh = RenderingEngine::GenerateTerrain();

    m_VertexCount = mesh.VertexCount();

    m_VertexBufferObject.Data(mesh.Vertices(),
                              m_VertexCount * sizeof(RenderingEngine::Vertex),
                              RenderingEngine::OpenGL::BufferUsage::StaticDraw);

    m_VertexArrayObject.BindAttribute(0, m_VertexBufferObject,
                                      RenderingEngine::OpenGL::Type::Float,
                                      3, sizeof(RenderingEngine::Vertex), 0);

    m_VertexArrayObject.BindAttribute(1, m_VertexBufferObject,
                                      RenderingEngine::OpenGL::Type::Float,
                                      2, sizeof(RenderingEngine::Vertex), sizeof(glm::vec3));
}

void RenderingEngine::Terrain::Render()
{
    RenderingEngine::OpenGL::Context::GetInstance()->DrawArrays(m_VertexArrayObject,
                                                                RenderingEngine::OpenGL::Primitive::Triangles,
                                                                0, m_VertexCount);
}
