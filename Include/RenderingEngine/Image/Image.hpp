#pragma once

#include <RenderingEngine/OpenGL/Color.hpp>
#include <RenderingEngine/OpenGL/Texture.hpp>
#include <string>

namespace RenderingEngine
{
    struct Image
    {
        Image();
        explicit Image(const std::string& filename);
        Image(const Image& image);
        Image(Image&& image) noexcept;

        Image(uint32_t width, uint32_t height, const OpenGL::Color& background);
        Image(uint32_t width, uint32_t height, OpenGL::Color* const data);

        virtual ~Image();

        Image& operator=(const Image& image);
        Image& operator=(Image&& image) noexcept;

        OpenGL::Texture ConstructTexture() const;

        const uint32_t GetWidth() const;
        const uint32_t GetHeight() const;
        const OpenGL::Color* const GetPixels() const;

        OpenGL::Color GetPixel(uint32_t x, uint32_t y) const;
        void SetPixel(uint32_t x, uint32_t y, const OpenGL::Color& color);

    private:
        OpenGL::Color* m_ImageData;
        uint32_t m_Width, m_Height;
    };
}
