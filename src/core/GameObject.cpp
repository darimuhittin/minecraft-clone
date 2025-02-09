#include "core/GameObject.h"
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(const glm::vec3& position)
    : m_Position(position)
    , m_Rotation(0.0f)
    , m_Scale(1.0f)
{
}

glm::mat4 GameObject::GetTransform() const
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, m_Position);
    transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::scale(transform, m_Scale);
    return transform;
} 