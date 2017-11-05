#include <Infrastructure/GameModule.hpp>
#include <EventProcessing/EventProcessing.hpp>
#include <EventProcessing/EventHandler.hpp>
#include <RenderingEngine/Camera.hpp>
#include <iostream>

static void OnKeyPressed(EventProcessing::KeyCode keyCode, uint32_t deltaTime)
{
    glm::vec3 position = RenderingEngine::Camera::GetInstance()->GetPosition();
    glm::vec3 rotation = RenderingEngine::Camera::GetInstance()->GetRotation();
    float speed = 3.0f;
    float distance = speed * ((float)deltaTime / 1000);

    switch (keyCode)
    {
        case EventProcessing::KeyCode::W:
            RenderingEngine::Camera::GetInstance()->SetPosition(position + rotation * distance);
            break;

        case EventProcessing::KeyCode::A:
            RenderingEngine::Camera::GetInstance()->SetPosition(position - glm::cross(rotation, glm::vec3 {0.0f, 0.0f, 1.0f}) * distance);
            break;

        case EventProcessing::KeyCode::S:
            RenderingEngine::Camera::GetInstance()->SetPosition(position - rotation * distance);
            break;

        case EventProcessing::KeyCode::D:
            RenderingEngine::Camera::GetInstance()->SetPosition(position + glm::cross(rotation, glm::vec3 {0.0f, 0.0f, 1.0f}) * distance);
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

void OnFrame(uint32_t)
{
    glm::vec3 position = RenderingEngine::Camera::GetInstance()->GetPosition();
    std::cout << position.x << " " << position.y << " " << position.z << std::endl;
}

bool ModuleInit()
{
    EventProcessing::EventHandler::GetInstance()->RegisterKeyPressedCallback(OnKeyPressed);
    EventProcessing::EventHandler::GetInstance()->RegisterOnFrameCallback(OnFrame);
    return true;
}
