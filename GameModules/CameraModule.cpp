#include <Infrastructure/GameModule.hpp>
#include <RenderingEngine/Camera.hpp>
#include <Infrastructure/Settings.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/vector_angle.hpp>

#ifdef _DEBUG
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
            RenderingEngine::Camera::GetInstance()->SetPosition(position - glm::cross(rotation, upVector) * distance);
            break;

        case EventProcessing::KeyCode::S:
            RenderingEngine::Camera::GetInstance()->SetPosition(position - rotation * distance);
            break;

        case EventProcessing::KeyCode::D:
            RenderingEngine::Camera::GetInstance()->SetPosition(position + glm::cross(rotation, upVector) * distance);
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
#else
static void OnKeyPressed(EventProcessing::KeyCode keyCode, uint32_t deltaTime)
{
	glm::vec3 position = RenderingEngine::Camera::GetInstance()->GetPosition();
	glm::vec3 rotation = RenderingEngine::Camera::GetInstance()->GetRotation();
	float speed = 3.0f;
	if (EventProcessing::EventHandler::GetInstance()->IsKeyPressed(EventProcessing::KeyCode::SHIFT))
	{
		speed = 6.0f;
	}
	float distance = speed * ((float)deltaTime / 1000);
	glm::vec3 upVector{ 0.0f, 0.0f, 1.0f };

	switch (keyCode)
	{
	case EventProcessing::KeyCode::W:
		RenderingEngine::Camera::GetInstance()->SetPosition(position + glm::vec3{rotation.x, rotation.y, 0.0f} * distance);
		break;

	case EventProcessing::KeyCode::A:
		RenderingEngine::Camera::GetInstance()->SetPosition(position - glm::cross(rotation, upVector) * distance);
		break;

	case EventProcessing::KeyCode::S:
		RenderingEngine::Camera::GetInstance()->SetPosition(position - glm::vec3{ rotation.x, rotation.y, 0.0f } * distance);
		break;

	case EventProcessing::KeyCode::D:
		RenderingEngine::Camera::GetInstance()->SetPosition(position + glm::cross(rotation, upVector) * distance);
		break;

	default:
		break;
	}
}
#endif

static void OnMouseMove(int32_t deltaX, int32_t deltaY)
{
#if _DEBUG
    if (!EventProcessing::EventHandler::GetInstance()->IsKeyPressed(EventProcessing::KeyCode::MOUSE_LEFT))
    {
        return;
    }
#endif

    glm::vec3 rotation = RenderingEngine::Camera::GetInstance()->GetRotation();
    glm::vec3 rotationAxis {0.0f, 0.0f, 1.0f};
    glm::vec3 upVector {0.0f, 0.0f, 1.0f};
    glm::vec3 pitchAxis = glm::cross(glm::normalize(glm::vec3 {rotation.x, rotation.y, 0.0f}), upVector);

    float sensitivity = Settings::GetInstance()->GetMouseSensitivity();
    int pitchMultiplier = Settings::GetInstance()->IsMouseReversed() ? -1 : 1;

    rotation = glm::vec4(rotation, 0.0f) * glm::rotate(sensitivity * deltaX, rotationAxis);

	glm::vec3 tempRotation = rotation;
    rotation = glm::vec4(rotation, 0.0f) * glm::rotate(pitchMultiplier * sensitivity * deltaY, pitchAxis);

	if (glm::abs(glm::dot(glm::normalize(rotation), upVector)) > 0.9)
	{
		rotation = tempRotation;
	}

    RenderingEngine::Camera::GetInstance()->SetRotation(rotation);
}

GAME_MODULE()
{
    REGISTER_CALLBACK(KeyPressed, OnKeyPressed);
	REGISTER_CALLBACK(OnMouseMove, OnMouseMove);
    return true;
}
