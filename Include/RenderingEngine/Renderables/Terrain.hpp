#pragma once

#include <RenderingEngine/Renderables/Renderable.hpp>
#include <RenderingEngine/Mesh/Mesh.hpp>

#include <RenderingEngine/OpenGL/OpenGL.hpp>

namespace RenderingEngine
{
    struct Terrain : public Renderable
    {
        Terrain();

        void Render();

    private:
        OpenGL::VertexArray m_VertexArrayObject;
        OpenGL::VertexBuffer m_VertexBufferObject;

        size_t m_VertexCount;
    };
}
