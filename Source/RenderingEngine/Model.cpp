#include <RenderingEngine/Model.hpp>

RenderingEngine::Model::Model() :
    m_VertexCount { 0 }
{}

void RenderingEngine::Model::UploadMesh(const RenderingEngine::Mesh& mesh)
{
    m_VertexCount = mesh.VertexCount();

    m_VertexBufferObject.Data(mesh.Vertices(),
                              m_VertexCount * sizeof(RenderingEngine::Vertex),
                              RenderingEngine::OpenGL::BufferUsage::StaticDraw);

    m_VertexArrayObject.BindAttribute(0, m_VertexBufferObject,
                                      RenderingEngine::OpenGL::Type::Float,
                                      3, sizeof(RenderingEngine::Vertex), 0);
}

void RenderingEngine::Model::Render()
{
    RenderingEngine::OpenGL::Context::GetInstance()->DrawArrays(m_VertexArrayObject,
                                                                RenderingEngine::OpenGL::Primitive::Triangles,
                                                                0,
                                                                m_VertexCount);
}