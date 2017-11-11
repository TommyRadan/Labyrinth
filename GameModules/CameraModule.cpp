#include <Infrastructure/GameModule.hpp>
#include <EventProcessing/EventProcessing.hpp>
#include <EventProcessing/EventHandler.hpp>
#include <RenderingEngine/Camera.hpp>
#include <Infrastructure/Settings.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/vector_angle.hpp>

static void OnKeyPressed(EventProcessing::KeyCode keyCode, uint32_t deltaTime)
{
    glm::vec3 position = RenderingEngine::Camera::GetInstance()->GetPosition();
    glm::vec3 rotation = RenderingEngine::Camera::GetInstance()->GetRotation();
    float speed = 3.0f;
    if (EventProcessing::EventHandler::GetInstance()->IsKeyPressed(EventProcessing::KeyCode::SHIFT))
    {
        speed = 30.0f;
    }
    float distance = speed * ((float)deltaTime / 1000);
    glm::vec3 upVector {0.0f, 0.0f, 1.0f};

    switch (keyCode)
    {
        case EventProcessing::KeyCode::W:
            RenderingEngine::Camera::GetInstance()->SetPosition(position + rotation * distance);
            break;

        case EventProcessing::KeyCode::A:
            RenderingEngine::Camera::GetInstance()->SetPosition(position - glm::cross(rotation,
                                                                                      upVector) * distance);
            break;

        case EventProcessing::KeyCode::S:
            RenderingEngine::Camera::GetInstance()->SetPosition(position - rotation * distance);
            break;

        case EventProcessing::KeyCode::D:
            RenderingEngine::Camera::GetInstance()->SetPosition(position + glm::cross(rotation,
                                                                                      upVector) * distance);
            break;

        case EventProcessing::KeyCode::SPACE:
            RenderingEngine::Camera::GetInstance()->SetPosition({position.x, position.y, position.z + distance});
            break;

        case EventProcessing::KeyCode::CTRL:
            RenderingEngine::Camera::GetInstance()->SetPosition({position.x, position.y, position.z - distance});
            break;

        default:
            break;
    }
}

static void OnMouseMove(int32_t deltaX, int32_t deltaY)
{
    if (!EventProcessing::EventHandler::GetInstance()->IsKeyPressed(EventProcessing::KeyCode::MOUSE_LEFT))
    {
        return;
    }

    glm::vec3 rotation = RenderingEngine::Camera::GetInstance()->GetRotation();
    glm::vec3 rotationAxis {0.0f, 0.0f, 1.0f};
    glm::vec3 upVector {0.0f, 0.0f, 1.0f};
    glm::vec3 pitchAxis = glm::cross(glm::normalize(glm::vec3 {rotation.x, rotation.y, 0.0f}), upVector);

    float sensitivity = Settings::GetInstance()->GetMouseSensitivity();
    int pitchMultiplier = Settings::GetInstance()->IsMouseReversed() ? -1 : 1;

    rotation = glm::vec4(rotation, 0.0f) * glm::rotate(-sensitivity * deltaX, rotationAxis);
    rotation = glm::vec4(rotation, 0.0f) * glm::rotate(pitchMultiplier * sensitivity * deltaY, pitchAxis);

    RenderingEngine::Camera::GetInstance()->SetRotation(rotation);
}

bool ModuleInit()
{
    EventProcessing::EventHandler::GetInstance()->RegisterKeyPressedCallback(OnKeyPressed);
    EventProcessing::EventHandler::GetInstance()->RegisterOnMouseMoveCallback(OnMouseMove);
    return true;
}
