#include <RenderingEngine/Camera.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/transform.hpp>
#include <Infrastructure/Settings.hpp>

Camera::Camera()
{
    m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
    m_LookAt = glm::vec3(1.0f, 0.0f, 0.0f);
    m_Rotation = glm::normalize(m_LookAt - m_Position);

    const Settings* settings = Settings::GetInstance();

    m_FieldOfView = settings->GetFieldOfView();
    m_AspectRatio = settings->GetAspectRatio();
    m_NearClip = 0.1f;
    m_FarClip = 10000.0f;
    m_Perspective = glm::perspective(m_FieldOfView, m_AspectRatio, m_NearClip, m_FarClip);

    m_IsViewMatrixDirty = true;
}

Camera* Camera::GetInstance()
{
    static Camera* instance = nullptr;

    if(instance == nullptr)
    {
        instance = new Camera();
    }

    return instance;
}

void Camera::SetPosition(const glm::vec3& pos)
{
    m_Position = pos;
    m_IsViewMatrixDirty = true;
}

void Camera::SetRotation(const glm::vec3& rotation)
{
    m_Rotation = rotation;
    m_LookAt = m_Position + glm::normalize(m_Rotation);
    m_IsViewMatrixDirty = true;
}

void Camera::SetLookAt(const glm::vec3& lookAt)
{
    m_LookAt = lookAt;
    m_Rotation = glm::normalize(m_LookAt - m_Position);
    m_IsViewMatrixDirty = true;
}

glm::mat4 Camera::GetViewMatrix()
{
    if (!m_IsViewMatrixDirty)
    {
        return m_ViewMatrix;
    }

    glm::vec3 upVector(0.0f, 0.0f, 1.0f);
    m_ViewMatrix = glm::lookAt(m_Position, m_LookAt, upVector);
    m_IsViewMatrixDirty = false;
    return m_ViewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix(void)
{
    return m_Perspective;
}
