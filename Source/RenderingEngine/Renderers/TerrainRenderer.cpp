#include <RenderingEngine/Renderers/TerrainRenderer.hpp>

static std::string vertexShader = R"vs(
        #version 330

        layout(location=0) in vec3 position;
        layout(location=1) in vec2 uv;

        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;

        out vec2 texCoord;

        void main()
        {
            mat4 MVP = projectionMatrix * viewMatrix;
            gl_Position = MVP * vec4(position, 1.0);

            texCoord = uv;
        }
)vs";

static std::string fragmentShader = R"fs(
        #version 330

        in vec2 texCoord;
        uniform sampler2D tex;
        out vec4 fragColor;

        void main()
        {
            fragColor = texture(tex, texCoord);
        }
)fs";

RenderingEngine::Renderers::TerrainRenderer::TerrainRenderer()
{
    ConstructProgram(vertexShader, fragmentShader);
}

RenderingEngine::Renderers::TerrainRenderer* RenderingEngine::Renderers::TerrainRenderer::GetInstance()
{
    static TerrainRenderer* instance = nullptr;

    if (instance == nullptr)
    {
        instance = new TerrainRenderer;
    }

    return instance;
}

RenderingEngine::Renderers::TerrainRenderer::~TerrainRenderer()
{
    DestructProgram();
}
