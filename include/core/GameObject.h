#pragma once

#include <glm/glm.hpp>
#include "graphics/Renderer.h"

class GameObject {
public:
    GameObject(const glm::vec3& position = glm::vec3(0.0f));
    virtual ~GameObject() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Render(Renderer& renderer) = 0;

    const glm::vec3& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; }

    const glm::vec3& GetRotation() const { return m_Rotation; }
    void SetRotation(const glm::vec3& rotation) { m_Rotation = rotation; }

    const glm::vec3& GetScale() const { return m_Scale; }
    void SetScale(const glm::vec3& scale) { m_Scale = scale; }

    glm::mat4 GetTransform() const;

protected:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;
}; 