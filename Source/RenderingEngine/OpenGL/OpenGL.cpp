#include <RenderingEngine/OpenGL/OpenGL.hpp>

namespace RenderingEngine::OpenGL
{
    Context* Context::GetInstance()
    {
        static Context *instance { nullptr };

        if (instance == nullptr)
        {
            instance = new Context();
        }

        return instance;
    }

    void Context::Init()
    {
        if (glewInit() != GLEW_OK)
        {
            throw Exception("Could not initialize OpenGL");
        }

        int versionMajor, versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        if(versionMajor < 3 || (versionMajor == 3 && versionMinor < 3))
        {
            throw Exception("The game requires at least OpenGL version 3.3");
        }
    }

    void Context::Quit()
    {}

    void Context::Enable(const OpenGL::Capability capability)
    {
        glEnable((GLenum)capability);
    }

    void Context::Disable(const OpenGL::Capability capability)
    {
        glDisable((GLenum)capability);
    }

    void Context::ClearColor(const Color& color)
    {
        glClearColor(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
    }

    void Context::Clear(const OpenGL::Buffer buffers)
    {
        glClear((GLbitfield)buffers);
    }

    void Context::DepthMask(const bool writeEnabled)
    {
        glDepthMask(writeEnabled ? GL_TRUE : GL_FALSE);
    }

    void Context::BindTexture(const OpenGL::Texture& texture, const unsigned char unit)
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, texture.Handle());
    }

    void Context::BindFramebuffer(const OpenGL::Framebuffer& framebuffer)
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer.Handle());

        // Set viewport to frame buffer size
        GLint obj, width, height;
        glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &obj);

        GLint res;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &res);
        glBindTexture(GL_TEXTURE_2D, obj);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
        glBindTexture(GL_TEXTURE_2D, res);

        glViewport(0, 0, width, height);
    }

    void Context::BindFramebuffer()
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

        // Set viewport to default frame buffer size
        //glViewport(m_DefaultViewport[0], m_DefaultViewport[1], m_DefaultViewport[2], m_DefaultViewport[3]);

        /*
         * TODO: Fix glViewport for returning to default framebuffer
         */
    }

    void Context::DrawArrays(const OpenGL::VertexArray& vao, const OpenGL::Primitive mode, const unsigned int offset, const unsigned int vertices)
    {
        glBindVertexArray(vao.Handle());
        glDrawArrays((GLenum)mode, offset, vertices);
        glBindVertexArray(0);
    }

    void Context::DrawElements(const OpenGL::VertexArray& vao, const OpenGL::Primitive mode, const intptr_t offset, const unsigned int count, const unsigned int type)
    {
        glBindVertexArray(vao.Handle());
        glDrawElements((GLenum)mode, count, type, (const GLvoid*)offset);
        glBindVertexArray(0);
    }
}
