#pragma once

#include <RenderingEngine/OpenGL/Color.hpp>
#include <string>

namespace RenderingEngine
{
    struct Image
    {
        Image();
        Image(const std::string& filename);
        Image(const Image& image);
        Image(Image&& image) noexcept;

        Image(const uint32_t width, const uint32_t height, const OpenGL::Color& background);
        Image(const uint32_t width, const uint32_t height, OpenGL::Color* const data);

        virtual ~Image();

        Image& operator=(const Image& image);
        Image& operator=(Image&& image) noexcept;

        const uint32_t GetWidth() const;
        const uint32_t GetHeight() const;
        const OpenGL::Color* const GetPixels() const;

        OpenGL::Color GetPixel(const uint32_t x, const uint32_t y) const;
        void SetPixel(const uint32_t x, const uint32_t y, const OpenGL::Color& color);

    private:
        OpenGL::Color* m_ImageData;
        uint32_t m_Width, m_Height;
    };
}
