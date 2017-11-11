#include <RenderingEngine/Image/Image.hpp>

#include <Infrastructure/Exception.hpp>
#include <RenderingEngine/Image/StbImageLoader.hpp>

RenderingEngine::Image::Image() :
        m_ImageData { nullptr },
        m_Width { 0u },
        m_Height { 0u }
{}

RenderingEngine::Image::Image(const std::string& filename)
{
    int numComponents;
    m_ImageData = (RenderingEngine::OpenGL::Color*) stbi_load(filename.c_str(),
                                                              (int*)&m_Width,
                                                              (int*)&m_Height,
                                                              &numComponents, 4);

    if (m_ImageData == nullptr)
    {
        throw Exception("Could not load image (" + filename + ")");
    }
}

RenderingEngine::Image::Image(const Image& image) :
        m_Width { image.m_Width },
        m_Height { image.m_Height },
        m_ImageData { new OpenGL::Color[image.m_Width * image.m_Height] }
{
    memcpy(m_ImageData, image.m_ImageData, m_Width * m_Height * sizeof(OpenGL::Color));
}

RenderingEngine::Image::Image(Image&& image) noexcept :
        m_Width { image.m_Width },
        m_Height { image.m_Height },
        m_ImageData { image.m_ImageData }
{
    image.m_Width = 0u;
    image.m_Height = 0u;
    image.m_ImageData = nullptr;
}

RenderingEngine::Image::Image(uint32_t width, uint32_t height, const OpenGL::Color& background) :
        m_ImageData { new OpenGL::Color[width * height] },
        m_Width { width },
        m_Height { height }
{
    for (uint32_t i = 0; i < width * height; ++i)
    {
        m_ImageData[i] = background;
    }
}

RenderingEngine::Image::Image(uint32_t width, uint32_t height, OpenGL::Color* const data) :
        m_ImageData { data },
        m_Width { width },
        m_Height { height }
{}

RenderingEngine::Image::~Image()
{
    if (m_ImageData == nullptr) return;
    delete[] m_ImageData;
}

RenderingEngine::Image& RenderingEngine::Image::operator=(const Image& image)
{
    m_Width = image.m_Width;
    m_Height = image.m_Height;
    memcpy(m_ImageData, image.m_ImageData, m_Width * m_Height * sizeof(OpenGL::Color));
    return *this;
}

RenderingEngine::Image& RenderingEngine::Image::operator=(Image&& image) noexcept
{
    m_Width = image.m_Width;
    m_Height = image.m_Height;
    m_ImageData = image.m_ImageData;

    image.m_Width = 0u;
    image.m_Height = 0u;
    image.m_ImageData = nullptr;
    return *this;
}

RenderingEngine::OpenGL::Texture RenderingEngine::Image::ConstructTexture() const
{
    RenderingEngine::OpenGL::Texture texture;
    texture.Image2D(GetPixels(),
                    RenderingEngine::OpenGL::DataType::UnsignedByte,
                    RenderingEngine::OpenGL::Format::RGBA,
                    GetWidth(),
                    GetHeight(),
                    RenderingEngine::OpenGL::InternalFormat::RGBA);

    texture.SetWrappingR(RenderingEngine::OpenGL::Wrapping::Repeat);
    texture.SetWrappingS(RenderingEngine::OpenGL::Wrapping::Repeat);
    texture.SetWrappingT(RenderingEngine::OpenGL::Wrapping::Repeat);
    texture.SetFilters(RenderingEngine::OpenGL::Filter::LinearMipmapNearest,
                       RenderingEngine::OpenGL::Filter::NearestMipmapLinear);
    texture.GenerateMipmaps();

    return texture;
}

const unsigned int RenderingEngine::Image::GetWidth() const
{
    return m_Width;
}

const unsigned int RenderingEngine::Image::GetHeight() const
{
    return m_Height;
}

const RenderingEngine::OpenGL::Color* const RenderingEngine::Image::GetPixels() const
{
    return m_ImageData;
}

RenderingEngine::OpenGL::Color RenderingEngine::Image::GetPixel(uint32_t x, uint32_t y) const
{
    if (x >= m_Width || y >= m_Height) return OpenGL::Color();
    return m_ImageData[x + y * m_Width];
}

void RenderingEngine::Image::SetPixel(uint32_t x, uint32_t y, const OpenGL::Color& color)
{
    if (x >= m_Width || y >= m_Height) return;
    m_ImageData[x + y * m_Width] = color;
}
