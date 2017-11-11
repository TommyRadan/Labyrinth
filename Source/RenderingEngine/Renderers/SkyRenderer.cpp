#include <RenderingEngine/Renderers/SkyRenderer.hpp>

static std::string vertexShader = R"vs(
        #version 330

        layout(location=0) in vec3 position;

        uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;

        out vec3 fragPosition;

        void main()
        {
            mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
            gl_Position = MVP * vec4(position, 1.0);
            fragPosition = position;
        }
)vs";

static std::string fragmentShader = R"fs(
        #version 330

        out vec4 fragColor;
        in vec3 fragPosition;

        uniform sampler2D sky;

        void main()
        {
            vec3 fragDirection = normalize(fragPosition);

            float horizontProximity = abs(1.0 - dot(vec3(0.0, 0.0, 1.0), fragDirection));

            fragColor = texture(sky, vec2(0.0, horizontProximity));
        }
)fs";

RenderingEngine::Renderers::SkyRenderer::SkyRenderer()
{
    ConstructProgram(vertexShader, fragmentShader);
}

RenderingEngine::Renderers::SkyRenderer* RenderingEngine::Renderers::SkyRenderer::GetInstance()
{
    static SkyRenderer* instance = nullptr;

    if (instance == nullptr)
    {
        instance = new SkyRenderer;
    }

    return instance;
}

RenderingEngine::Renderers::SkyRenderer::~SkyRenderer()
{
    DestructProgram();
}
