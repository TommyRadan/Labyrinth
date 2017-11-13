#pragma once

#include <glm.hpp>

namespace RenderingEngine
{
    struct Renderable
    {
        Renderable();

        void SetPosition(const glm::vec3& position);
        void SetRotation(const glm::vec3& rotation);
        void SetScale(const glm::vec3& scale);

        glm::vec3 GetPosition() const;
        glm::vec3 GetRotation() const;
        glm::vec3 GetScale() const;

        glm::mat4 GetModelMatrix() const;

    private:
        mutable glm::mat4 m_ModelMatrix;
        mutable bool m_IsModelMatrixDirty;

        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        glm::vec3 m_Scale;
    };
}
