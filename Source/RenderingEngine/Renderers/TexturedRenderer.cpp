#include <RenderingEngine/Renderers/TexturedRenderer.hpp>

static std::string vertexShader = R"vs(
        #version 330

        layout(location=0) in vec3 position;
        layout(location=1) in vec2 uv;

		uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;

        out vec2 texCoord;

        void main()
        {
            mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
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

RenderingEngine::Renderers::TexturedRenderer::TexturedRenderer()
{
	ConstructProgram(vertexShader, fragmentShader);
}

RenderingEngine::Renderers::TexturedRenderer* RenderingEngine::Renderers::TexturedRenderer::GetInstance()
{
	static TexturedRenderer* instance = nullptr;

	if (instance == nullptr)
	{
		instance = new TexturedRenderer;
	}

	return instance;
}

RenderingEngine::Renderers::TexturedRenderer::~TexturedRenderer()
{
	DestructProgram();
}
