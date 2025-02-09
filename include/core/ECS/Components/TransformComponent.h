#pragma once

#include "core/ECS/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformComponent : public Component {
public:
    TransformComponent(const glm::vec3& position = glm::vec3(0.0f),
                      const glm::vec3& rotation = glm::vec3(0.0f),
                      const glm::vec3& scale = glm::vec3(1.0f))
        : m_Position(position)
        , m_Rotation(rotation)
        , m_Scale(scale)
    {}

    const glm::vec3& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

    const glm::vec3& GetRotation() const { return m_Rotation; }
    void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

    const glm::vec3& GetScale() const { return m_Scale; }
    void SetScale(const glm::vec3& scale) { m_Scale = scale; }

    glm::mat4 GetTransformMatrix() const {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, m_Position);
        transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, m_Scale);
        return transform;
    }

private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
}; 