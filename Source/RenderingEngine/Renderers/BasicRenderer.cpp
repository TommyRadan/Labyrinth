#include <RenderingEngine/Renderers/BasicRenderer.hpp>

static std::string vertexShader = "" \
        "#version 330\n" \
        "\n" \
        "layout(location = 0) in vec4 vert;\n" \
        "void main() { gl_Position = vert; }\n";

static std::string fragmentShader = "" \
        "#version 330\n" \
        "out vec4 fragColor;\n" \
        "void main() { fragColor = vec4(1.0, 1.0, 1.0, 1.0); }\n";

RenderingEngine::Renderers::BasicRenderer::BasicRenderer()
{
    ConstructProgram(vertexShader, fragmentShader);
}

RenderingEngine::Renderers::BasicRenderer::~BasicRenderer()
{
    DestructProgram();
}

void RenderingEngine::Renderers::BasicRenderer::SetupCamera()
{}
