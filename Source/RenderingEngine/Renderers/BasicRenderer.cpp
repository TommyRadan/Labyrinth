#include <RenderingEngine/Renderers/BasicRenderer.hpp>
#include <RenderingEngine/Camera.hpp>

static std::string vertexShader = "" \
        "#version 330\n" \
        "\n" \
        "layout(location=0) in vec3 position;\n" \
        "\n" \
        "uniform mat4 viewMatrix;\n" \
        "uniform mat4 projectionMatrix;\n" \
        "void main() { \n" \
        "mat4 VP = projectionMatrix * viewMatrix;\n" \
        "gl_Position = VP * vec4(position, 1.0);\n" \
        "}\n";

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
{
    this->UploadMatrix4("viewMatrix", RenderingEngine::Camera::GetInstance()->GetViewMatrix());
    this->UploadMatrix4("projectionMatrix", RenderingEngine::Camera::GetInstance()->GetProjectionMatrix());
}
